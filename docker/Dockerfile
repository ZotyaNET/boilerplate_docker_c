FROM debian:bookworm-slim

# Install required dependencies
RUN apt-get update && apt-get install -y \
    curl \
    g++ \
    make \
    libsqlite3-dev \
    libgtest-dev \
    wget && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Install the latest version of CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0-linux-x86_64.sh && \
    chmod +x cmake-3.30.0-linux-x86_64.sh && \
    ./cmake-3.30.0-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-3.30.0-linux-x86_64.sh

# Set the working directory
WORKDIR /app

# Copy the source code into the container (include CMakeLists.txt)
COPY . /app

# Create a clean build directory, configure, and build the project
RUN rm -rf /app/cmake-build-debug && \
    mkdir -p /app/cmake-build-debug && \
    cd /app/cmake-build-debug && \
    cmake -S ../ && \
    cmake --build . --target docker_c

# Set the default command to run the built executable
CMD ["./cmake-build-debug/docker_c"]