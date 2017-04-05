#########################################################################
# File Name: com.sh
# Author: ZX
# mail: 18829897183@163.com
# Created Time: Mon 03 Apr 2017 07:07:56 PM PDT
#########################################################################
#!/bin/bash

ROOT_PATH=$(pwd)
INCLUDE=$ROOT_PATH
SRC=$(ls *.c | tr '\n' ' ')
OBJ=$(ls *.c | sed 's/\.c//g' | tr '\n' ' ')
SERVER_NAME=httpd
CC=gcc
LIB=-lpthread

cat <<EOF >Makefile
${SERVER_NAME}:${OBJ}
	${CC} -o \$@ \$^ $LIB


.PHONY:clean
clean:
	rm -f *.o $SERVER_NAME
EOF
