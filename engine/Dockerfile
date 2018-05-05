FROM alpine:3.7

# RUN esed -i 's/dl-cdn.alpinelinux.org/mirrors.ustc.edu.cn/g' /etc/apk/repositories
RUN apk update && \
    apk add make cmake g++

ADD . /src
RUN cd /src && \
    ./configure && \
    make
