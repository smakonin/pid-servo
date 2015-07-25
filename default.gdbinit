file project.o
set remotebaud 38400
target dbug12 ttylink
monitor bf 1000 7fff 55
load
set *0xb34 = 0
set *0xb36 = 0
set *0xdb4e = 0x84ff

