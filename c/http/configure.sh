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
#OBJ=$(ls *.c | sed 's/\.c//g' | tr '\n' ' ')
SERVER_NAME=httpd
CC=gcc
LIB=-lpthread

#cgi
CGI_PATH=$ROOT_PATH/cgi/
MATH_SRC=$(ls $CGI_PATH | grep 'math' | grep -E '.c$')
MATH_CGI_BIN=cgi_math
#cgi Makefile
cat <<EOF > $CGI_PATH/Makefile
${MATH_CGI_BIN}:$MATH_SRC
	$CC -o \$@ \$^
.PHONY:clean
clean:
	rm -f $MATH_CGI_BIN
.PHONY:output
output:
	cp $MATH_CGI_BIN ..
EOF

#TOP Makefile
cat <<EOF >Makefile
${SERVER_NAME}:${SRC}
	${CC} -o \$@ \$^ $LIB

.PHONY:all
all:${SERVR_NAME} cgi

.PHONY:cgi
cgi:
	cd cgi; make; make output; cd -
	mkdir -p wwwroot/cgi_bin/
	cp -rf cgi/cgi_math wwwroot/cgi_bin
.PHONY:clean
clean:
	rm -rf *.o $SERVER_NAME output; cd cgi;make clean;cd - 

.PHONY:output
output:
	mkdir output
	cp ${SERVER_NAME} output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi/cgi_math output/wwwroot/cgi_bin/
EOF
