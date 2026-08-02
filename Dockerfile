FROM ubuntu:26.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    libboost-all-dev \
    libeigen3-dev \
    python3 \
    python3-numpy \
    python3-requests \
    python3-pip \
    pybind11-dev \
    pkg-config \
    libx11-dev \
    libopenblas-dev \
    liblapack-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt
RUN git clone https://github.com/davisking/dlib.git
WORKDIR /opt/dlib
RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-fPIC" .. && \
    cmake --build . -j$(nproc) --config Release --target all && \
    cmake --install .

WORKDIR /app
COPY . /app/aicpp
WORKDIR /app/aicpp
RUN [ -e ARC-AGI-2 ] || git clone https://github.com/arcprize/ARC-AGI-2.git
WORKDIR /app/aicpp/scripts
RUN [ -e arc-dsl ] || git clone https://github.com/Julien-Livet/arc-dsl.git
WORKDIR /app/aicpp
RUN mkdir -p build
RUN cmake -S . -B build
RUN cmake --build build --config Release --target all -- -j$(nproc)

ENTRYPOINT ["/bin/bash"]

CMD ["-c", "cd build && ./test_aicpp"]
