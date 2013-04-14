#coding:utf8
import os
import sys
sn = sys.argv[1]

f = open('tem.h').read()
nf = open('%s.h'%(sn), 'w')
nf.write(f.replace('[NAME]', sn))
nf.close()


f = open('tem.cpp').read()
nf = open('%s.cpp'%(sn), 'w')
nf.write(f.replace('[NAME]', sn))
nf.close()


f = open('../proj.linux/temMake').read()
nf = open('../proj.linux/Makefile', 'w')
nf.write(f.replace('[NAME]', sn))
nf.close()

