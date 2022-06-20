# Creating a programming language from scratch

This project is a tutorial for myself to learn how to create my own programming language. I decided to write all the code in C. Below is a list of things that I would like to try:

- a lexer
- a parser
- an interpreter
- produce native executables

The development compiler is [Tiny C Compiler aka. `tcc`](https://bellard.org/tcc/). It compiles code really fast.

## Getting started

### Install `tcc` if you don't already have it

1. Go to [this URL](http://download.savannah.gnu.org/releases/tinycc/) and download the appropriate version
2. Extract the downloaded zip file where-ever you like
3. Add the path to the `tcc` executable file into your environment
4. Confirm that it works by running `tcc --help`

### Clone this repository

On the command line (if you have `git` installed):

```sh
git clone https://github.com/santerijps/programming-language-tutorial
```

### Compile the binaries

With `make`:

```sh
cd programming-language-tutorial
make
```

With `tcc`:

```sh
cd programming-language-tutorial
mkdir bin
tcc src/pltc.c -o bin/pltc
```

### Try the examples

```sh
cd programming-language-tutorial
bin/pltc examples/example.py
```
