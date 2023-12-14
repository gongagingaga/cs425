# Results for Assignment 03

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _Finish time_ in the
network tab of the developer tools.

| Version | Time | Speedup | Changes |
| :-----: | ---- | :-----: | ------- |
| [01](server.cpp) | 30.80 seconds | &mdash; | Initial version - no changes |
| [02](server1.cpp) | 25.50 seconds | 1.2 times faster | Created asynchronous tasks(the two lines of code route). |
| [03](server2.cpp) | &mdash; | &mdash; | Created a ring buffer for the producer and consumer setup, however something is broken and it will not run |

## Profiling Analysis

### Review

The first attempt was simply to get the server to thread and see how much it would change, however, as the instructions may have implied, there was usually almost no change, I have no clue as to if there was an anomally getting a 5 second difference a few times. 
After this I tried to create a ring buffer consumer/producer system, with the help of internet tutorials, and I only got so far before this error began to plague me:

[Connection.h:63] bytesRead = ::recv(_client, &data[bytesRead], bufferSize, 0) failed: Bad file descriptor

I tried my best to parse the functions and wrappers in Connection.h but alas, I am too frail minded as I am now, so I was unable to understand what could possibly be causing this problem. It must be something that I did in my ring buffer implementation, as the Connection.h still works with the original server.cpp but in the end I wasn't able to find the bug. 
