
.PHONY:all
all:tserver client
	
client:client.c
	gcc -o $@ $^ -lpthread
tserver:tserver.c
	gcc -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -f tserver client

