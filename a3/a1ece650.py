#!/usr/bin/env python3
import sys
import re
from street import Street
from graph import Graph
import os

# YOUR CODE GOES HERE
def parse(line, g):
    line = " ".join(line.split())
    split_result = re.fullmatch(r'(.) (.*)', line)
    if split_result.group(1) == 'a':
        g.add(Street(split_result.group(2)))
    elif split_result.group(1) == 'r':
        old_st = re.fullmatch(r'"(.*)"', split_result.group(2))
        g.remove(old_st.group(1))
    elif split_result.group(1) == 'c':
        g.change(split_result.group(2))
    else:
        raise Exception()


def main():
    # YOUR MAIN CODE GOES HERE
    # sample code to read from stdin.
    # make sure to remove all spurious print statements as required
    # by the assignment
    g = Graph()
    while True:
        sys.stdout.flush()
        line = sys.stdin.readline()
        line = line.strip('\n')
        if line == "" or line == 'eof':
            print("")
            break
        if line =='g':
            # print the graph
            sys.stdout.flush()
            g.display()
        else:
            try:
                parse(line, g)
            except:
                print("Error: something is wrong")

    # return exit code 0 on successful termination
    sys.exit(0)


if __name__ == "__main__":
    main()
