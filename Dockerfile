FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y software-properties-common && \
    apt-get install -y g++ cmake libwt-dev libwthttp-dev libboost-all-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN g++ -o smart_quiz code.cpp -lwt -lwthttp

ENV PORT=8080
EXPOSE 8080

CMD ["./smart_quiz", "--docroot=.", "--http-address=0.0.0.0", "--http-port=8080"]
