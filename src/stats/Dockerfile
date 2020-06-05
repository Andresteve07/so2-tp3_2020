# This is the second and final image; it copies the compiled
# binary over but starts from the base ubuntu:18.04 image.
FROM ubuntu:latest
#ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install -y --no-install-recommends \
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
COPY --from=so2-tp3-builder /app/exec/stats .
RUN ls -halt
CMD ["./stats"]