### C++ Based Solution of GateOfIshtar
* Author : Fahad Umer 
* Version : v1.0
This document contains necessary details on problems which have been fixed and compiler falgs, version and build enviroment information.


### Fixed Issues
##### 1. Logging in data efficiently with ring buffer
In the previous implementation, data time intervals are being stored in a list which is not very effective way of Logging data as a monotonically increasing amount of data will be produced over a period of time resulting in significant amount of disk space for effective logging. 
In the current C++ based solution, a ring buffer is used for data logging which is fast and will also avert failures due to running out of space.


##### 2. Synchronization in case of multi threaded application
Previous implementation has race conditions which can arise in multithreaded environment where a shared data buffer is used by both the producer and consumer of date time intervals. As each of the threads (producer and consumer) try to write to the global shared space, it is necessary to take care that they write to the memory in sync, or else the date time intrevals will get corrupted. 
The current C++ based solution has locking mechanism implemented in circular buffer class to avoid such situations.


##### 3. Implemented missing functions and optimized code
In the previous implementation, 
* holly_day function implementation is missing
* too many if else conditions have been used while the same could be achieved with a simple return statement

Above mentioned problems have been fixed in C++ bases solution


##### 4. Champion should only lose HP once every hour
In the previous implementation, we are only taking into consideration time difference between two consecutive intervals while It can happen that time difference between two consecutive intervals is less than an hour but is greater than an hour between the first and last element of buffer. Such corner cases were not handled in previous solution.


##### 5. Integer underflow 
Total damage taken by a champion was subtracted from initial HP which can lead towards potential problem of integer underflow if the total damage exceeds the initial HP. In C++ based such underflow has been taker care of.


##### 6. Time duration overlapping
Previously, time duration for “brand” and "Ahri" were overlapping which will result in huge incorrect damage. Overlapping durations have been fixed.


##### 7. Error handling
Throw exception if class construction goes wrong due to some hardware fatal error or internal implementation. Moreover, trigger error if something goes wrong with the ring buffer.


##### 8. Added main class for testing 
Adding a testmain file for functionality testing and demo purpose.


### Compilation Information
* **Compiler and Version** :  
    - Version        :  4.9.2
    - Architecture   : x86_64
    - Threads        : posix
    - Exception      : seh
    - Build revision : 1
* **Compiler flags** : -O2 -g3 -Wall -c -fmessage-length=0 -std=c++0x
