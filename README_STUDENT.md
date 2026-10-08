# CSE 220 Homework 4 Starter Kit

Read the assignment description first. It has the full rules, all the examples,
and the grading breakdown. This file only covers how to build and run things.

## What is in here

    Makefile              builds everything into build/
    strgPtr.h             Part 1 prototypes, do not change
    strgPtr.c             Part 1, write your code here
    caesar.h              Part 2 prototypes, do not change
    caesar.c              Part 2, write your code here
    tests/test_strgPtr.c  your Part 1 Criterion tests
    tests/test_caesar.c   your Part 2 Criterion tests

## Building and running

    make          build your code and the tests into build/
    make test     build if needed, then run every test
    make clean    remove build/
    make objects  compile only strgPtr.c and caesar.c, without Criterion

The Makefile compiles with `-Wall -Wextra -Werror -std=c11`, so any warning
stops the build. The starter kit compiles as given, and the sample tests fail
until you implement the functions. That is expected.

## Criterion

The tests use Criterion, which is already installed on the lab machines, so
`make test` works there with no setup.

On your own machine, install it first:

    macOS (Homebrew):   brew install criterion
    Ubuntu or Debian:   sudo apt install libcriterion-dev

The Makefile finds Criterion through pkg-config, and falls back to
`-lcriterion` if pkg-config does not know about it.

## What you have to write

* The six functions in `strgPtr.c`.
* The two functions in `caesar.c`. These must use your own `strgLen` whenever
  they need the length of a string.
* At least 5 Criterion tests per function in the two files under `tests/`,
  which is 40 tests in total. Your tests are worth 25% of each part.

You may not use `<string.h>` or `<ctype.h>`. You may use `<stddef.h>`, which
the headers already include for you, and `<stdio.h>` while you debug.

## Submitting

Zip the whole folder, including the `Makefile`, both headers, both `.c` files
and the `tests/` folder, and upload it to Brightspace as

    FALLCSE220-<SBUusername>-<SBUID>.zip

Do not include `build/`. Run `make clean` first.
