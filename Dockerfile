FROM ubuntu:24.04

# Install build essentials and dependencies for CMake
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    curl \
    wget \
    ca-certificates \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Install latest CMake (precompiled binary)
ENV CMAKE_VERSION=3.30.0
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz \
    && tar -xzf cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz --strip-components=1 -C /usr/local \
    && rm cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz

# Verify CMake version
RUN cmake --version

WORKDIR /usr/src/app

# Copy project files
COPY . .

# Clean any old build artifacts
RUN rm -rf build CMakeCache.txt CMakeFiles

# Build project
RUN mkdir -p build && cd build && cmake .. && cmake --build .

# Default number of cores
ENV NUM_CORES=0

# Run executable
CMD if [ "$NUM_CORES" -gt 0 ]; then \
        CORE_LIST=$(seq -s, 0 $((NUM_CORES-1))); \
        echo "Running ./Lab with cores: $CORE_LIST"; \
        taskset -c $CORE_LIST ./build/Lab; \
    else \
        ./build/Lab; \
    fi
