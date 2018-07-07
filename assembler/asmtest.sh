#! /bin/bash

python assembler.py -f test.asm -o test && hexdump test
