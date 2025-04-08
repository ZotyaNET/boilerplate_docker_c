FROM debian:bookworm-slim

# Install required dependencies
RUN apt-get update && apt-get install -y \
    curl \
    g++ \
    make \
    wget && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Install the latest version of CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0-linux-x86_64.sh && \
    chmod +x cmake-3.30.0-linux-x86_64.sh && \
    ./cmake-3.30.0-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-3.30.0-linux-x86_64.sh

# Set the working directory
WORKDIR /app

# Copy the source code into the container
COPY ./ /app/src

# Create a build directory, configure, and build the project
RUN mkdir -p build && \
    cd build && \
    cmake ../src && \
    make -j$(nproc)

# Set the default command to run the built executable
CMD ["./build/docker_c"]