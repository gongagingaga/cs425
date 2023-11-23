#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <deque>
#include <mutex>
#include <condition_variable>
#include "Connection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

uint16_t DefaultPort = 8114;
const size_t BufferSize = 5;


std::deque<std::packaged_task<HTTPResponse()>> taskBuffer;
std::mutex bufferMutex;
std::condition_variable bufferNotEmpty;

void producer() {
    Connection connection(DefaultPort);

    while (connection) {
        Session session(connection.accept());

        std::packaged_task<HTTPResponse()> task([&session]() -> HTTPResponse {
            std::string msg;
            session >> msg;

            HTTPRequest request(msg);

            const char* root = "/home/faculty/shreiner/public_html/03";
            HTTPResponse response(request, root);

            return response;
        });

        {
            std::unique_lock<std::mutex> lock(bufferMutex);
            taskBuffer.push_back(std::move(task));
        }

        bufferNotEmpty.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(bufferMutex);
        bufferNotEmpty.wait(lock, [] { return !taskBuffer.empty(); });

        std::packaged_task<HTTPResponse()> task = std::move(taskBuffer.front());
        taskBuffer.pop_front();

        lock.unlock();

        task(); 
    }
}

int main(int argc, char* argv[]) {
	DefaultPort = argc > 1 ? std::stol(argv[1]) : DefaultPort;	
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}

