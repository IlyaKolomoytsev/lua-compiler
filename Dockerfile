# Base Ubuntu Linux image
FROM ubuntu:22.04

ENV JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64

# Install package dependencies
RUN apt-get update &&  \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    cmake \
    bison \
    flex \
    graphviz \
    gdb \
    openjdk-21-jdk-headless \
    maven \
    && rm -rf /var/lib/apt/lists/*

ENV HOME=/home/builder

RUN useradd -m builder

# Copy project to working directory
WORKDIR /app
COPY . /app

RUN chown -R builder:builder /app

# Maven repo
RUN mkdir -p /home/builder/.m2 && chown -R builder:builder /home/builder

USER builder

# Build
RUN cmake . && make

# Run command
CMD ["./lua_compiler"]
