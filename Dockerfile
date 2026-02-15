FROM gcc:12-bookworm

WORKDIR /app

RUN apt-get update && \
apt-get install -y make bats && \
rm -rf /var/lib/apt/list/*

COPY src/ ./src/
COPY test/ ./test/
COPY Makefile .
RUN make 
CMD make test
