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
** java
```
sudo apt-get install default-jdk -y
```

** sbt
```
echo "deb https://dl.bintray.com/sbt/debian /" | sudo tee -a /etc/apt/sources.list.d/sbt.list
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 642AC823
sudo apt-get update
sudo apt-get install sbt -y
```

** verilator
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

### Build with docker
```
rosrun pal_deploy deploy.py -p trust_package tiago-27c
```

### Download docker image


## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds


## Directories

### Client
Conține pagina componente serverului web pentru interfața robotului. Esti o aplicație web one page.
Partea de html se află în index.html unde aplicația este împărțită în 3 module:
* Modulu Hartă, unde este afișată calea pe hartă de la robot la standul ENSTA
* Modulul Logo, unde este afișat logo-ul ENSTA
* Modulul Chestionar, care este împărțită în 3 submodule: partea cu butonul START, partea cu întrebările chestionarului și partea cu mesajul de mulțumire

Fișierele javascript sunt în subdirectorul /js iar cele interne sunt:
* dashboard.js care conține logica pentru hartă și logica de schimbare între module
* functions.js care conține logica pentru descărcarea răspunsurilor întrebărilor pentru chestionar în format csv
* hmi.js partea pentru conectarea la rosbridge
* hbba.js date pentru desire ale sitemului (ar putea fi eliminat)
* language.js partea care încarcă ce limbă va fi folosită și fișierele aferente
* start_recording.js partea care se ocupă de submodulul cu butonul START
* record_questions.js partea care se ocupă de submodul cu întrebările chestionarului și submodul cu mesajul de mulțumire

În subdirectorul /js se află un alt director json care conține json-uri pentru întrebările chestionarului și mesajele afișate pentru difertie limbi

Fișierele css se află în subdirectoare /css și /font-awesome. Singurul element intern este /css/start.css

Subdirectorul img conține imaginea cu logo-ul ENSTA

### Config
Conține configurări pentru sistemul central. Directorul este împărțit în:
* subdirectorul maps care conține cât un director pentru fiecare hartă folosită
* subdirectorul sounds care conține fișierele audio ce vor fi redate de sistemul central
* fișiere de forma x_poi.json conțin datele despre puncte de interes prezente pe harta x
* fișiere de forma x_info.json conțin date suplimentare despre punctele de interes prezente pe harta x

### Launch
Conține fișierele de launch pentru pachetul ros.
* bib_poli_launch.launch conține detalii despre nodurile ce trebuie pornite pentru un experiment

### Logs
Fost director în care erau păstrate logurile. Deoarece nu e recomandat să se scrie în sursa unui pachet acesta va fi retras din uz sau va fi folosit pentru datele ce vor fi analizate după terminarea experimentului

### Scripts
Conține scripturile bash și python ce vor fi rulate în timpul experiemntului. Acestea sunt:
* bib_poly_face_dect.py  un modul de test pentru detectare fețelor cu dlib, nefolosit în experiment, dar bun pentru o testare a functionalității librăriei dlib
* bib_poli_install_http un script bash care copiază fișierele pentru serverul http în directorul de pe tiago unde este încărcat serverul apache. Al doilea lucru pe care îl face după e de a porni pagina dedicată experiemntului în interfața web
* bib_poly_key_teleop.py un modul de control manual al robotului Tiago prin tastatură. viteza robotului poate fi setată prin parametrul ros aflat la calea `/trust_package/experiment/speed`
* bib_poly_look_after_old.py modul de test pentru diferite variante de a face robotul de a se întoarce către o personă, am renunțat la acest modul în cadrul experimentului deoarece dorim ca robotul să se întoarcă către grupul cu cele mai multe persoane
* bib_poly_look_after.py modulul care se ocupă ca robotul să aleagă orientrea spre grupul cu cele mai multe persoane. Acesta face o piruietă de 360 de grade scanând numărul de persoane, după care se întoare către grupul de persoane cel mai mare
* bib_poli_after_manual_interface.py modulul care se ocupă de trimiterea comenzilor manual către sistemul central
* bib_poli_poi_manager.py modulul care se ocupă de încărcarea punctelor de interes din fișiere
* bib_poli_prime.py modulul care reprezintă modulul central
* bib_poli_record_audio.sh modul bash care se ocupă de înregistrarea audio a întregului experiment
* bib_poli_rosbag_merge.py un script python care concateneaza rosbag-urile din timpul interacțiunii
* bib_poli_rosbag.py modulul care se ocupă de înregistrrarea rosbag-urilor în timpul interacțiunii

## Experiment logic
![Alt text](BibPoliDiagram.png?raw=true "Central System Logic")

Legend:
Topic_p Topic publisher
Topic_s Topic permanent subscriber
Topic_so Topic one time subscriber

![Alt text](BibpoliModuleInteractions.png?raw=true "Module interactions")



## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Ciocîrlan Ștefan-Dan** - *Algorithms and building the system work* - [sdcioc](https://github.com/sdcioc)

See also the list of [contributors](https://github.com/sdcioc/caial.git/contributors) who participated in this project.

## License

This project is licensed under the BSD 3-Clause License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* NUS

