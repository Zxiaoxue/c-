httpd:httpd.c main.c 
	gcc -o $@ $^ -lpthread

.PHONY:all
all: cgi

.PHONY:cgi
cgi:
	cd cgi; make; make output; cd -
	mkdir -p wwwroot/cgi_bin/
	cp -rf cgi/cgi_math wwwroot/cgi_bin
.PHONY:clean
clean:
	rm -rf *.o httpd output; cd cgi;make clean;cd - 

.PHONY:output
output:
	mkdir output
	cp httpd output/
	cp -rf log output/
	cp -rf conf output/
	cp -rf wwwroot output/
	mkdir -p output/wwwroot/cgi_bin
	cp -f cgi/cgi_math output/wwwroot/cgi_bin/
