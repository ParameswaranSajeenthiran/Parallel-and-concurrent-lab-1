cmake_minimum_required(VERSION 3.29.6)
project(Lab C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab main.c
        linkedList.c
        linkedList.h
        tests/Serial.c
        tests/Serial.h
        tests/Config.c
        tests/Config.h
        tests/Mutex.c
        tests/Mutex.h
        tests/Constants.h
        tests/ReadWriteLock.c
        tests/ReadWriteLock.h
        tests/unit/linkedListUnit.c
)
target_link_libraries(Lab m)
