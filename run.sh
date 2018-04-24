#!/bin/bash
./update.sh Makefile
make
./avm $1
