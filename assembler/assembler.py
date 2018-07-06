import argparse
import struct
import re
from enum import Enum

parser = argparse.ArgumentParser()
parser.add_argument("-o", help="output file path", type=str, default='z.out')
parser.add_argument("-f", help="input file path", type=str, required=True)
args = parser.parse_args()

byte_count = 0
d, s = first_pass()
second_pass(d, s)

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


def parse_tok_2(s):
    if re.match('^0x', s):
        return int(s, 16)
    elif re.match('[1-9][0-9]+', s):
        return int(s)
    elif re.match('[_\w]+', s):
        return s
    else:
        print('error parsing tok_2')

def first_pass():
    directives = []
    symbols = {}
    line_nu = 0

    global byte_count   # stupid python scope resolution

    byte_count = 0

    def push_as_byte(b):
        global byte_count
        byte_count += 1
        as_bytes = bytes([b])
        directives.append(Directive(DirectiveType.INST, as_bytes))

    def push_as_wide(w):
        if type(w) == str:
            directives.append(Directive(DirectiveType.ID, w))
        else:
            global byte_count
            byte_count += 2
            as_bytes = bytes(struct.pack("<H", w))
            directives.append(Directive(DirectiveType.INST, as_bytes))

    with open(args.f, 'r') as file:
        file_text = file.read()

    for line in file_text.splitlines():
        line_nu += 1

        # remove comments
        line = re.sub(';[^\n\r]*','', line)

        print(line_nu, '\t\t', line)

        statement = re.findall("[^\s]+", line)

        if len(statement) == 0:
            continue

        tok_1 = statement[0]
        tok_2 = 0

        if len(statement) > 1:
            tok_2 = parse_tok_2(statement[1])

        if re.match('[_\w][_\w0-9]*:$', tok_1):
            name = tok_1[:-1]
            symbols[name] = byte_count

        elif tok_1 == '.byte':
            push_as_byte(tok_2)

        elif tok_1 == '.wide':
            push_as_wide(tok_2)

        elif tok_1 == 'noop':
            push_as_byte(0x00)

        elif tok_1 == 'addi':
            push_as_byte(0x10)
            push_as_byte(tok_2)

        elif tok_1 == 'subi':
            push_as_byte(0x11)
            push_as_byte(tok_2)

        elif tok_1 == 'add':
            push_as_byte(0x20)
            push_as_wide(tok_2)

        elif tok_1 == 'sub':
            push_as_byte(0x21)
            push_as_wide(tok_2)

        elif tok_1 == 'clac':
            push_as_byte(0x30)

        elif tok_1 == 'stor':
            push_as_byte(0x40)
            push_as_wide(tok_2)

        elif tok_1 == 'beqz':
            push_as_byte(0x50)
            push_as_wide(tok_2)

        elif tok_1 == 'cset':
            push_as_byte(0xe0)
            push_as_byte(tok_2)

        elif tok_1 == 'vset':
            push_as_byte(0xe1)
            push_as_wide(tok_2)

        elif tok_1 == 'halt':
            push_as_byte(0xff)

        else:
            print('unrecognized opcode, line %d: %s' % (line_nu, line))
            exit(1)

    return directives, symbols


def second_pass(directives, symbols):
    output_stream = open(args.o, 'wb')

    def write_as_wide(w):
        as_bytes = bytes(struct.pack("<H", w))
        output_stream.write(as_bytes)

    for directive in directives:
        if directive.type == DirectiveType.INST:
            output_stream.write(directive.value)
        elif directive.type == DirectiveType.ID:
            addr = symbols[directive.value]
            write_as_wide(addr)

    output_stream.close()
