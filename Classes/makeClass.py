#coding:utf8
import os
import sys

name = sys.argv[1]
f = open('template.h').read()
head = open('%s.h' % name, 'w')
head.write(f.replace('[NAME]', name))
head.close()

f = open('template.cpp').read()
body = open('%s.cpp' % name, 'w')
body.write(f.replace('[NAME]', name))
body.close()
