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
    python3-venv \
    python3-numpy \
    python3-requests \
    python3-pip \
    pybind11-dev \
    pkg-config \
    libx11-dev \
    libopenblas-dev \
    liblapack-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app/aicpp
WORKDIR /app/aicpp
RUN [ -e ARC-AGI-2 ] || git clone https://github.com/arcprize/ARC-AGI-2.git
WORKDIR /app/aicpp/scripts
RUN [ -e arc-dsl ] || git clone https://github.com/Julien-Livet/arc-dsl.git
WORKDIR /app/aicpp
RUN mkdir -p build
RUN cmake -S . -B build -DWITHOUT_HODEL_TASKS=ON
RUN cmake --build build --config Release --target all -- -j$(nproc)
RUN python3 -m venv .venv && . .venv/bin/activate && python -m pip install -r requirements.txt
 
ENTRYPOINT ["/bin/bash"]
