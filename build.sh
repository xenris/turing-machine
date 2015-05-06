#!/bin/sh

OUTPUT=bin/turing
SOURCE=src/*.c

mkdir -p bin/

gcc -std=gnu99 $SOURCE -o $OUTPUT
