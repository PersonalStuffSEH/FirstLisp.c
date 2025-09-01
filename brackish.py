from sys import maxsize
import re

COMMENT = "$"

with open("./test.brac", "r") as file:
    contents = file.readlines()

# remove the comments
for line_idx, line in enumerate(contents):
    for char_idx, char in enumerate(line):
        if char == COMMENT:
            contents[line_idx] = line[:char_idx:]

# remove trailing whitespaces
contents = "".join(map(lambda line: re.sub("\\s+", " ", line).strip(), contents))

# ast gen
def generate(string, key):
    ast = {}
    running = ""
    idx = 0
    for char_idx, char in enumerate("".join(string)):
        if char_idx < idx:
            continue
        if char == '(':
            idx, sub = generate(string[char_idx+1::], running)
            # ast[running] = ast.get(running, [])
            # ast[running].append(sub)
        elif char == ')':
            print(running)
            # ast[key] = ast.get(key, [])
            # ast[key].append(running)
            # return char_idx, ast
        else:
            running += char
    return [char_idx, {}]

import pprint
pprint.pprint(generate(contents, ""), sort_dicts=1)
