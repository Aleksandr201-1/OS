#! /usr/bin/env python3

# -*- coding: utf-8 -*-

import sys
import random

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print( "Usage: {0} <count of tests>".format( sys.argv[0] ) )
        sys.exit(1)

    tst_file = open( sys.argv[1], 'w' )
    ans_file = open( sys.argv[2], 'w' )
    size = int( sys.argv[3] )

    tst_file.write("{0}\n".format(size))

    mas = []

    for _ in range(size):
        i = random.randint(0,1000)
        mas.append(i)
        tst_file.write("{0} ".format(i))
    mas.sort()
    for i in range(size):
        ans_file.write("{0} ".format(mas[i]))
    ans_file.write("\n")
    tst_file.close()
    ans_file.close()