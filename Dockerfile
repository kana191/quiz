FROM ubuntu:22.04

# Prevent user prompts (non-interactive build)
ARG DEBIAN_FRONTEND=noninteractive

# Update and install dependencies
RUN apt-get update && \
    apt-get install -y software-properties-common && \
    apt-get install -y g++ cmake libwt-dev libwthttp-dev libboost-all-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Compile the Wt C++ app
RUN g++ -o smart_quiz code.cpp -lwt -lwthttp

# Define the port Railway will use
ENV PORT=8080
EXPOSE 8080

# Run the app with Wt server
CMD ["./smart_quiz", "--docroot=.", "--http-address=0.0.0.0", "--http-port=8080"]
