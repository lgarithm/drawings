#!/usr/bin/env python
import sys
s = sys.stdin.read()
for i in range(0, len(s), 80):
    print s[i : i + 80]
