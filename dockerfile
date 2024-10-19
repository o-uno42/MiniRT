# Start with a base image that has the necessary development tools
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install required packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
	zlib1g-dev \
	libbsd-dev \
    xorg \
    wget \
    git \
    cmake \
    make \
    gcc \
    g++ \
    libbsd-dev \
    && apt-get clean

# Set up directories for your project and copy the code
WORKDIR /usr/src/app

# Copy your project files into the container
COPY . .

# Build libft and minilibx libraries
RUN make -C libft
RUN make -C minilibx-linux

# Compile your project using the Makefile
RUN make all

# Command to run your executable when the container starts
CMD ["./minirt"]

