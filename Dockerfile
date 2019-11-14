FROM ubuntu:18.04
RUN apt-get update \
  && apt-get install -y libncurses-dev make gcc
RUN mkdir /work
WORKDIR /work
ENTRYPOINT make
  
