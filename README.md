# Fortrend Backend Platform

Educational backend project in C++23 focused on Linux, networking, asynchronous I/O, databases, distributed systems, highload and production engineering.

## Current Features

- C++23
- CMake + Ninja
- GCC
- environment-based configuration
- typed application error model
- structured JSON logging
- GoogleTest + CTest
- ASan + UBSan
- graceful `SIGINT` / `SIGTERM` shutdown

## Build

```bash
cmake --preset linux-gcc-debug
cmake --build --preset linux-gcc-debug