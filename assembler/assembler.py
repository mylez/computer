import argparse
import re
import struct
from enum import Enum


class DirectiveType(Enum):
    INST = 1
    ID = 2


class Directive:
    def __init__(self, type, value):
        self.type = type
        self.value = value

    def get_byte_count(self):
        if self.type == DirectiveType.ID:
            return 0
        return len(self.value)


class FirstPassBuilder:
    def __init__(self):
        self.segment = '.text'

        self.data = []
        self.text = []
        self.data_byte_count = 0
        self.text_byte_count = 0
        self.data_symbols = {}
        self.text_symbols = {}

    def set_segment(self, s):
        self.segment = s

    def push_as_byte(self, b):
        self.incr_bytes(1)
        as_bytes = bytes([b])
        self.segment_directives().append(Directive(DirectiveType.INST, as_bytes))

    def push_as_wide(self, w):
        if type(w) == str:
            self.incr_bytes(2)
            self.segment_directives().append(Directive(DirectiveType.ID, w))
        else:
            self.incr_bytes(2)
            as_bytes = bytes(struct.pack("<H", w))
            self.segment_directives().append(Directive(DirectiveType.INST, as_bytes))

    def segment_directives(self):
        if self.segment == '.text':
            return self.text
        elif self.segment == '.data':
            return self.data

    def set_symbol(self, symbol):
        if self.segment == '.text':
            self.text_symbols[symbol] = self.get_byte_count()
        elif self.segment == '.data':
            self.data_symbols[symbol] = self.get_byte_count()

    def incr_bytes(self, i):
        if self.segment == '.text':
            self.text_byte_count += i
        elif self.segment == '.data':
            self.data_byte_count += 1

    def get_byte_count(self):
        if self.segment == '.text':
            return self.text_byte_count
        elif self.segment == '.data':
            return self.data_byte_count


def parse_tok_2(s):
    if re.match('^0x', s):
        return int(s, 16)
    elif re.match('[1-9][0-9]*', s):
        return int(s)
    elif re.match('[_\w]+', s):
        return s
    else:
        print('error parsing tok_2')


def first_pass():
    line_nu = 0

    b = FirstPassBuilder()

    with open(args.f, 'r') as file:
        file_text = file.read()

    for line in file_text.splitlines():
        line_nu += 1

        # remove comments
        line = re.sub(';[^\n\r]*', '', line)

        statement = re.findall("[^\s]+", line)

        if len(statement) == 0:
            continue

        tok_1 = statement[0]
        tok_2 = 0

        if len(statement) > 1:
            tok_2 = parse_tok_2(statement[1])

        if re.match('[_\w][_\w0-9]*:$', tok_1):
            name = tok_1[:-1]
            b.set_symbol(name)

        elif tok_1 == '.text':
            b.set_segment('.text')

        elif tok_1 == '.data':
            b.set_segment('.data')

        elif tok_1 == '.byte':
            b.push_as_byte(tok_2)

        elif tok_1 == '.wide':
            b.push_as_wide(tok_2)

        elif tok_1 == 'noop':
            b.push_as_byte(0x00)

        elif tok_1 == 'addi':
            b.push_as_byte(0x10)
            b.push_as_byte(tok_2)

        elif tok_1 == 'subi':
            b.push_as_byte(0x11)
            b.push_as_byte(tok_2)

        elif tok_1 == 'add':
            b.push_as_byte(0x20)
            b.push_as_wide(tok_2)

        elif tok_1 == 'sub':
            b.push_as_byte(0x21)
            b.push_as_wide(tok_2)

        elif tok_1 == 'clac':
            b.push_as_byte(0x30)

        elif tok_1 == 'stor':
            b.push_as_byte(0x40)
            b.push_as_wide(tok_2)

        elif tok_1 == 'beqz':
            b.push_as_byte(0x50)
            b.push_as_wide(tok_2)

        elif tok_1 == 'tset':
            b.push_as_byte(0xb0)
            b.push_as_byte(tok_2)

        elif tok_1 == 'cset':
            b.push_as_byte(0xc0)
            b.push_as_byte(tok_2)

        elif tok_1 == 'cuns':
            b.push_as_byte(0xc1)
            b.push_as_byte(tok_2)

        elif tok_1 == 'vset':
            b.push_as_byte(0xd0)
            b.push_as_wide(tok_2)

        elif tok_1 == 'eset':
            b.push_as_byte(0xe0)
            b.push_as_wide(tok_2)

        elif tok_1 == 'halt':
            b.push_as_byte(0xff)

        else:
            print('unrecognized opcode, line %d: %s' % (line_nu, line))
            exit(1)

    return b


def second_pass(builder):
    symbols = {}
    data_offset = builder.text_byte_count

    for key in builder.text_symbols.keys():
        symbols[key] = builder.text_symbols[key]
    for key in builder.data_symbols.keys():
        symbols[key] = builder.data_symbols[key] + data_offset

    print('symbol table')
    for key in symbols.keys():
        print('\t', hex(symbols[key]), '\t', key)

    with open(args.o, 'wb') as output_stream:

        for d in builder.text:
            if d.type == DirectiveType.INST:
                output_stream.write(d.value)
            elif d.type == DirectiveType.ID:
                as_bytes = bytes(struct.pack("<H", symbols[d.value]))
                output_stream.write(as_bytes)

        for d in builder.data:
            if d.type == DirectiveType.INST:
                output_stream.write(d.value)
            elif d.type == DirectiveType.ID:
                as_bytes = bytes(struct.pack("<H", symbols[d.value]))
                output_stream.write(as_bytes)


parser = argparse.ArgumentParser()
parser.add_argument("-o", help="output file path", type=str, default='z.out')
parser.add_argument("-f", help="input file path", type=str, required=True)
args = parser.parse_args()
b = first_pass()
second_pass(b)
