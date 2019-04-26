FROM ubuntu:16.04
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y \
	git \
	autoconf \
	automake \
	autotools-dev \
	curl \
	libmpc-dev \
	libmpfr-dev \
	libgmp-dev \
	libusb-1.0-0-dev \
	gawk build-essential \
	bison \
	flex \
	texinfo \
	gperf \
	libtool \
	patchutils \
	bc \
	zlib1g-dev \
	device-tree-compiler \
	pkg-config \
	libexpat-dev \
	default-jdk \
	make \
	g++ \
	python-pip
RUN apt-get install -y apt-transport-https ca-certificates
RUN echo "deb https://dl.bintray.com/sbt/debian /" | tee -a /etc/apt/sources.list.d/sbt.list \
	&& apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 642AC823 \
	&& apt-get update \
	&& apt-get install -y sbt
RUN mkdir riscv \
	&& cd riscv \
	&& mkdir riscv-tools
RUN cd riscv \
	&& git clone http://git.veripool.org/git/verilator \
	&& cd verilator \
	&& git checkout verilator_4_006 \
	&& unset VERILATOR_ROOT \
	&& autoconf \
	&& ./configure \
	&& make \
	&& make install
ENV RISCV /riscv/riscv-tools
RUN cd riscv \
	&& git clone --recursive  https://github.com/freechipsproject/rocket-tools \
	&& cd rocket-tools \ 
	&& ./build.sh
ENV PATH $PATH:$RISCV/bin
ENV ROSCKETCHIP /riscv/rocket-chip
RUN cd riscv \
	&& git clone --recursive  https://github.com/ucb-bar/rocket-chip.git
RUN cd riscv \
	&& cd rocket-chip \
	&& cd emulator \
	&& make debug
RUN cd riscv \
	&& git clone --recursive  https://github.com/riscv/riscv-tests \
	&& cd riscv-tests \
	&& autoconf \
	&& ./configure --prefix=$RISCV/target \
	&& make \
	&& make install
ENV RISCVTESTS /riscv/riscv-tests
RUN git clone https://github.com/sdcioc/caial.git \
	&& apt-get -y install python-pip \
	&& pip install numpy

