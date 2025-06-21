FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

# Install basic tools
RUN apt-get update && apt-get install -y \
    g++ cmake make wget unzip libssl-dev zlib1g-dev libpng-dev libboost-all-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Wt from source
WORKDIR /wt
RUN wget https://github.com/emweb/wt/archive/refs/tags/4.10.0.zip && \
    unzip 4.10.0.zip && \
    cd wt-4.10.0 && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DSHARED_LIBS=OFF -DBoost_USE_STATIC_LIBS=OFF .. && \
    make -j4 && make install

# Set up your app
WORKDIR /app
COPY . .

# Compile your Wt C++ app
RUN wget https://github.com/emweb/wt/archive/refs/tags/4.10.0.zip && \
    unzip 4.10.0.zip && \
    cd wt-4.10.0 && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DSHARED_LIBS=OFF \
          -DBoost_USE_STATIC_LIBS=OFF \
          -DENABLE_SSL=ON \
          -DENABLE_JSON=ON \
          .. && \
    make -j4 && make install

    
# Define Railway port
ENV PORT=8080
EXPOSE 8080

# Run app
CMD ["./smart_quiz", "--docroot=.", "--http-address=0.0.0.0", "--http-port=8080"]
