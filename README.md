# Fortrend Backend Platform

Educational backend project in C++23 focused on Linux, networking, asynchronous I/O, databases, distributed systems, highload and production engineering.

## Current Features

- C++23
- CMake + Ninja
- GCC
- environment-based configuration
- configuration validation
- structured JSON logging

## Build

```bash
cmake --preset linux-gcc-debug
cmake --build --preset linux-gcc-debug
```

## Run

```bash
./build/linux-gcc-debug/fortrend_backend
```

Example with configuration:

```bash
FORTREND_ENV=production \
FORTREND_SERVICE_NAME=fortrend-backend \
./build/linux-gcc-debug/fortrend_backend
```

## Configuration

Supported environment variables:

- `FORTREND_SERVICE_NAME`
- `FORTREND_ENV`

Supported environments:

- `local`
- `development`
- `test`
- `production`

## Logging

The application writes structured JSON logs.

Example:

```json
{"timestamp":"2026-10-01T10:35:41.123Z","severity":"INFO","service":"fortrend-backend","environment":"local","message":"application started"}
```