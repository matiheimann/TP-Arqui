FROM debian:jessie
RUN apt-get update && apt-get -y install clang nasm make qemu
RUN apt-get -y install git
WORKDIR /root
VOLUME ["/root/X64"]
ADD clone.sh root/root clone.sh
CMD ["bash"]

