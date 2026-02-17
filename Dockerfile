FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    libeigen3-dev \
    python3 \
    python3-pip \
    pybind11-dev \
    clang-20 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

RUN git clone https://github.com/Julien-Livet/aicpp.git

WORKDIR /app/aicpp

RUN git clone https://github.com/arcprize/ARC-AGI-2.git

RUN mkdir build && cd build
RUN cmake -S . -B build '-DCMAKE_GENERATOR:STRING=Unix Makefiles' -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang-20 -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++-20 \
RUN cmake --build build --target test_aicpp
RUN make -j$(nproc)

RUN pip3 install --no-cache-dir requests numpy

ENTRYPOINT ["/bin/bash"]

CMD ["-c", "./build/test_aicpp"]
