import argparse
import re

parser = argparse.ArgumentParser()

parser.add_argument("-o", type=str, default='z.out')
parser.add_argument("-f", type=str, required=True)
args = parser.parse_args()

with open(args.f, 'r') as input_file:
    input_stream = input_file.read()

output_stream = open(args.o, 'wb')


def write_as_byte(b):
    as_bytes = bytes([b])
    output_stream.write(as_bytes)


for line in input_stream.splitlines():
    statement = re.findall("[^\s]+", line)

    if len(statement) == 0:
        continue

    opcode = statement[0]

    if opcode == 'addi':
        imm = int(statement[1])
        write_as_byte(0x10)
        write_as_byte(imm)
    elif opcode == 'subi':
        imm = int(statement[1])
        write_as_byte(0x11)
        write_as_byte(imm)
    elif opcode == 'add':
        imm = int(statement[1])
        write_as_byte(0x20)
        write_as_byte(imm)
    elif opcode == 'sub':
        imm = int(statement[1])
        write_as_byte(0x21)
        write_as_byte(imm)
    elif opcode == 'clac':
        write_as_byte(0x30)
    elif opcode == 'stor':
        imm = int(statement[1])
        write_as_byte(0x40)
        write_as_byte(imm)
    elif opcode == 'beqz':
        imm = int(statement[1])
        write_as_byte(0x50)
        write_as_byte(imm)
    elif opcode == 'halt':
        write_as_byte(0xff)

output_stream.close()
