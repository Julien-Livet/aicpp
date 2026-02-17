FROM ubuntu:26.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    libeigen3-dev \
    python3 \
    python3-numpy \
    python3-requests \
    python3-pip \
    pybind11-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

RUN git clone https://github.com/Julien-Livet/aicpp.git

WORKDIR /app/aicpp

RUN git clone https://github.com/arcprize/ARC-AGI-2.git

RUN mkdir build
RUN cmake -S . -B build
RUN cmake --build build --target test_aicpp -- -j$(nproc)

ENTRYPOINT ["/bin/bash"]

CMD ["-c", "cd build && ./test_aicpp"]
