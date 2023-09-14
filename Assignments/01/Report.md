# Results for Assignment 01

## Improvement Iterations

Here's a table showing the improvements I did to make the application go faster.  The **Time** column in the table represents the _wall-clock time_ for a program run.

| Version | Time | Speedup | Memory (KB) | Changes |
| :-----: | ---- | :-----: | :------: | ------- |
| [01](01.cpp) | 9.52s | &mdash; | 1041332 | Initial version - no changes |
| 02 | 6.40s | 1.49x | 1043320 | Compiled with -O1 for general optimization |
| 03 | 15.15s | .63x| 1041272 | Compiled with -Oz to see if optimizing size and using simpler(but still more) instructions would make overall preformance improve |
| 04 | 2.48s | 3.84x| 1041212 | Compiled with -Ofast, made it fast |

## Profiling Analysis

### Initial Review

After a thorough inspection of the code, I looked into trying to reduce the amount of function calls to the dot product function, as that was the most popular function according to the [gprof](analysis.txt). To reduce the function calls, I decided to make an attempt at having more inline computation rather than function calls, however, after a few hours, I couldn't get the correct output without the function. So I came to the conclusion that it would be more valuable to simply use the optimization flags. This worked out as expected, as the higher the optimization on the flag the better it preformed.
