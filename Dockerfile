# Base Ubuntu Linux image
FROM ubuntu:20.04

ENV JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64

# Install package dependencies
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update &&  \
    apt-get install -y \
    g++-10 \
    cmake \
    bison \
    flex \
    graphviz \
    gdb \
    openjdk-21-jdk-headless \
    maven \
    && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 100

# Copy project to working directory
WORKDIR /app
COPY . /app

# Build
RUN cmake . && make

# Run command
CMD ["./lua_compiler"]
