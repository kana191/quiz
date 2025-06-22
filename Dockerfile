FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

# Install basic tools
RUN apt-get update && apt-get install -y \
    g++ cmake make wget unzip \
    libssl-dev zlib1g-dev libpng-dev libjpeg-dev libboost-all-dev \
    libharfbuzz-dev libglib2.0-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Build Wt from source (NO SSL/JSON)
WORKDIR /wt
RUN wget https://github.com/emweb/wt/archive/refs/tags/4.10.0.zip && \
    unzip 4.10.0.zip && \
    cd wt-4.10.0 && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DSHARED_LIBS=OFF \
          -DENABLE_SSL=OFF \
          -DENABLE_JSON=OFF \
          -DBoost_USE_STATIC_LIBS=OFF \
          .. && \
    make -j2 && make install

# Copy your code
WORKDIR /app
COPY . .

# Build your app
RUN g++ -o smart_quiz code.cpp \
    -lwt -lwthttp \
    -lboost_system -lboost_filesystem -lboost_thread \
    -pthread

# Expose and run
ENV PORT=8080
EXPOSE 8080
CMD ["./smart_quiz", "--docroot=.", "--http-address=0.0.0.0", "--http-port=8080"]
