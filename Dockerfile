FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

# Install base tools and enable universe repo
RUN apt-get update && \
    apt-get install -y software-properties-common wget gnupg && \
    echo "deb http://archive.ubuntu.com/ubuntu focal universe" >> /etc/apt/sources.list && \
    apt-get update && \
    apt-get install -y g++ cmake libboost-all-dev libssl-dev zlib1g-dev libpng-dev && \
    apt-get install -y libwt-dev libwthttp-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy your code.cpp
COPY . .

# Compile your app
RUN g++ -o smart_quiz code.cpp -lwt -lwthttp

# Set the port Railway exposes
ENV PORT=8080
EXPOSE 8080

# Run the app
CMD ["./smart_quiz", "--docroot=.", "--http-address=0.0.0.0", "--http-port=8080"]
