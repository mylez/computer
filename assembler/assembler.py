import argparse
import struct
import re

parser = argparse.ArgumentParser()

parser.add_argument("-o", help="output file path", type=str, default='z.out')
parser.add_argument("-f", help="input file path", type=str, required=True)
args = parser.parse_args()

with open(args.f, 'r') as file:
    file_text = file.read()

output_stream = open(args.o, 'wb')


def write_as_byte(b):
    as_bytes = bytes([b])
    output_stream.write(as_bytes)


def write_as_word(w):
    as_bytes = bytes(struct.pack("<H", w))
    output_stream.write(as_bytes)


l = 0


for line in file_text.splitlines():

    l += 1

    statement = re.findall("[^\s]+", line)

    if len(statement) == 0:
        continue

    opcode = statement[0]

    if len(statement) > 1:
        imm = int(statement[1])

    if opcode == 'noop':
        write_as_byte(0x00)

    elif opcode == 'addi':
        write_as_byte(0x10)
        write_as_byte(imm)

    elif opcode == 'subi':
        write_as_byte(0x11)
        write_as_byte(imm)

    elif opcode == 'add':
        write_as_byte(0x20)
        write_as_word(imm)

    elif opcode == 'sub':
        write_as_byte(0x21)
        write_as_word(imm)

    elif opcode == 'clac':
        write_as_byte(0x30)

    elif opcode == 'stor':
        write_as_byte(0x40)
        write_as_word(imm)

    elif opcode == 'beqz':
        write_as_byte(0x50)
        write_as_word(imm)

    elif opcode == 'sset':
        write_as_byte(0xe0)
        write_as_byte(imm)

    elif opcode == 'halt':
        write_as_byte(0xff)
    else:
        print('unrecognized opcode, line %d: %s'%(l, line))
        exit(1)

output_stream.close()
