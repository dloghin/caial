# CAIAL

C simple AI algorithms for testing bprof on bare metal RISC-V roscket-chip.
Currently are implemented the the next AI algoritms Classification Tree (CT),K-nearest neighbors (KNN),Deep neural networks (DNN), Linear regresion (LR), Naive Bayes (NB), Suport Vector Machine (SVM) and K-Means (KMEANS). Their implementation is simple as possible and does not use any libraries.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites
Tested on Ubuntu 16.04

* Ubuntu 16.04 (inital setup)
```
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install git -y
mkdir -p riscv/riscv-tools
```

* rocket-tools requirments
```
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev -y
```
* chistel requirments

1. java
```
sudo apt-get install default-jdk -y
```

2. sbt
```
echo "deb https://dl.bintray.com/sbt/debian /" | sudo tee -a /etc/apt/sources.list.d/sbt.list
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 642AC823
sudo apt-get update
sudo apt-get install sbt -y
```

3. verilator
```
sudo apt-get install git make autoconf g++ flex bison -y
git clone http://git.veripool.org/git/verilator
cd verilator
git checkout verilator_4_006
unset VERILATOR_ROOT
autoconf
./configure
make
sudo make install
cd
```

* rocket-tools
```
git clone --recursive  https://github.com/freechipsproject/rocket-tools
cd rocket-tools
export RISCV=/riscv/rocket-tools
./build.sh
export PATH=$PATH:$RISCV/bin
echo "export RISCV=/riscv/rocket-tools" >> .bashrc
echo "export PATH=$PATH:$RISCV/bin" >> .bashrc
cd
```


* rocket chip
```
git clone --recursive  https://github.com/ucb-bar/rocket-chip.git
cd rocket-chip
export ROCKETCHIP=`pwd`
echo "export ROCKETCHIP="$ROCKETCHIP >> .bashrc
cd $ROCKETCHIP/emulator
make debug
cd
```
* riscv-tests
```
git clone --recursive https://github.com/riscv/riscv-tests
cd riscv-tests
autoconf
./configure --prefix=$RISCV/target
make
sudo make install
export RISCVTESTS=`pwd`
echo "export RISCVTESTS="$RISCVTESTS >> .bashrc
cd
```

* bprof requirments
```
sudo apt-get -y install python-pip
pip install numpy
```


### Installing

* Clone and build the repo
```
git clone https://github.com/sdcioc/caial.git
make
make simv
make strip
```

* Test the system

```
python parser.py  strip_simv.log output
```

## Running the tests

If you want to test one of the algorithms you have to do the next things:
Compile the algorithm
```
make APP=NAME_OF_THE_ALGORITHM

```
Simulate the algorithm
```
make simv APP=NAME_OF_THE_ALGORITHM

```
Delete the logs that are not necesary
```
make strip APP=NAME_OF_THE_ALGORITHM

```
Run the parser
```
python parser.py  strip_simv.log output

```


### Adding other programs

For adding another program just create directory with the program name.
Inside the directory write you code in the file with the name the same as the directory name
plus extension ".c".
Example:

```
mkdir NEWPROGRAM
cd NEWPROGRAM
touch NEWPROGRAM
...
cd ..
make APP=NEWPROGRAM
```

### Analyze the results

The results will be in the file with the name of the second argument to the parser plus
".csv" extension.

```
python parser.py  strip_simv.log output
cat output.csv
```

## Docker Deployment

If you want to use dockers. First you will have to install docker.
Ubuntu 16.04 tested
```
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
sudo apt-get install -y docker-ce

```

### Build the docker image
```
cd docker
docker build .
```

### Download docker image
```
docker pull sdcioc/bprofriscv:latest
```
Inside docker
```
cd caial
git pull
```


## Built With

* [Rocket-Chip](https://github.com/freechipsproject/rocket-chip) - The RISC-V processor used
* [Rocket-tools](https://github.com/freechipsproject/rocket-tools) - Tools for Rocket Chip and RISC-V tools
* [RISCV-TESTS](https://github.com/riscv/riscv-tests) - Tests for RISC-V cores


## Directories
All directories except docker represent an algorithm that can be used. The "docker" directory has a Dockerfile necesary for building the docker image.

## Experiment logic

TODO:



## Contributing
TODO:

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

TODO:

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Ciocîrlan Ștefan-Dan** - *Algorithms and building the system work* - [sdcioc](https://github.com/sdcioc)

See also the list of [contributors](https://github.com/sdcioc/caial.git/contributors) who participated in this project.

## License

This project is licensed under the BSD 3-Clause License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* NUS

