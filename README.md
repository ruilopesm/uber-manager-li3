# LI3

This project was developed for the LI3 (Software Labs III) class in the 1st semester of the 2nd year of the Computer Science and Engineering course at University of Minho. <br>
It consists of a query maker of 3 main files: drivers.csv, users.csv and rides.csv (just like Uber, the well-known application).
Each file contains correlated information that when running the project you're able to obtain in fractions of seconds. All of this stored in memory and without the use of any kind of database. <br>

The project has two main modes:<br>
- __Batch__: In this mode, the program is run with two arguments, the first one is the path to the folder where the input files are located and the second one corresponds to the path to a text file that contains a list of commands (queries) to be executed. The result of executing each command should be written in an individual file located in the "Resultados" folder of the root of the "trabalho-pratico" folder. The format of the command files and the result files are described in Section 4.<br>
- __Interactive__: In this mode, the program is run without arguments. In this mode, the group will provide an interactive menu containing all the information (instructions) necessary for the execution of each command (query). Here, each command is interpreted and executed individually, with the respective result displayed in the terminal. It is important to note that the initial phase of user interaction with the program corresponds to the introduction of the path to the folder where the input files are located.<br>

This project was fully developed in C with the assist of glib2 for most of the data structures used on it.

## Getting started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

To run this project you'll only need to have [gcc](https://gcc.gnu.org/) and [glib2](https://docs.gtk.org/glib/) installed on your machine.

### Installing

```
git clone https://github.com/dium-li3/grupo-69
cd grupo-69
```

### Running the project with batch mode
```
./programa-principal <path to *.csv files> <path to input file>
```

### Running the tests
For this project some unit test were made to ensure the code written was going smoothly.
To run them just do as follows:
```
make test
```

## Project developed by:

a100545,Daniel da Silva Pereira,danielsp45 

a100764,Duarte Afonso Freitas Ribeiro,DuduWater12 

a100643,Rui Lopes Martins,RuiL1904 

