# This is the first image:
FROM ubuntu:latest AS compile-image
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install -y --no-install-recommends apt-utils
RUN apt-get install -y --no-install-recommends \
        # compiler and cmake
        build-essential \
        cmake \
        dpkg-dev \
        gcc \
        make \
        # ulfius library
        libmicrohttpd-dev \
        libjansson-dev \
        libcurl4-gnutls-dev \
        libgnutls28-dev \
        libgcrypt20-dev \
        libsystemd-dev \
        libulfius-dev \
        && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
# Compile the binaries
RUN mkdir exec \
        && cd exec \
        && cmake .. \
        && make \
        && ls -halt
#RUN ls -halt /app/ejecutable
CMD ["true"]