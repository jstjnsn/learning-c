# learning-c

This repository contains some projects I'm working on to learn more about the C programming language.

## Lessons learned

# GCC

- On my 2015 x86 MacBook Pro, gcc is aliased to clang. When I use gcc in my Makefile, it will be different between my laptop and any other system. I added a check to the Makefile for the OS that is running the command.
- I installed gcc through homebrew on my laptop, which took a long time. This is because homebrew builds gcc from source and because my laptop is quite old.

### Makefile

- Make has powerful wildcards to automate compiling c code, including header dependencies.

### Unit testing

- In C you can easily make unit tests by using the assert.h library.

### Github Actions

- Github actions is very easy to set up and runs fast.

## Inspired by

- https://github.com/codecrafters-io/build-your-own-x?tab=readme-ov-file#build-your-own-operating-system
