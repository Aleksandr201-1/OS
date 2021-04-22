#! /usr/bin/env python3

# -*- coding: utf-8 -*-

import sys
import random
import string

def get_random_key():
    i = random.randint(1,10)
    key = ""
    for _ in range(i):
        key += random.choice( string.ascii_letters )
    return key

if __name__ == "__main__":
    test = open("test", 'w')
    ans = open("ans", 'w')
    test.write("{0}\n".format(sys.argv[1]))
    test.write("{0}\n".format(sys.argv[2]))
    for _ in range( random.randint(1, 10 ** 3) ):
        key = get_random_key()
        test.write("{0}\n".format(key))
        if key[0] >= 'A' and key[0] <= 'Z':
            ans.write("{0}\n".format(key))
        else:
            ans.write("ERROR\n")
