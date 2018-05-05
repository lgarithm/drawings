FROM ubuntu:bionic

ADD sources.list.ustc /etc/apt/sources.list
RUN apt update && \
    apt install -y make cmake g++

ADD . /src
RUN cd /src && \
    ./configure && \
    make
