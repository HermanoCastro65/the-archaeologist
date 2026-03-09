# ============================================================
# Para usar este container no PowerShell rode:
#
# docker build -t archaeologist-tests .
# docker run --rm archaeologist-tests
#
# ============================================================

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    python3 \
    python3-pip \
    curl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN chmod +x build.sh

CMD ["./build.sh"]