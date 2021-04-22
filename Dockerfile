#
# The new base image to contain runtime dependences
#
FROM ubuntu:latest AS base
LABEL product="spdlog-cmake"
LABEL description="base"
LABEL MANTAINER="kewen"
ENV TZ="Asia/Shanghai"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    #
    # Install C++ tools
    ca-certificates \
    libyaml-cpp-dev \
    libgtest-dev \
    git \
    uuid-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    build-essential \
    cmake \
    locales \
    tzdata \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8 \
    && locale-gen zh_CN.GB18030 zh_CN.GBK \
    && rm -rf /var/lib/apt/lists/*

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone \
    && dpkg-reconfigure --frontend noninteractive tzdata


COPY . /usr/src

# Install gRPC and its dependencies
RUN mkdir -p "/usr/src/build"   \
    && cd "/usr/src/build"      \
    && cmake ..                 \
    -DCMAKE_BUILD_TYPE=Release  \
    && make -j                  \
    && cp spdlog_cmake /usr/local/bin
