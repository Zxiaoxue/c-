cli=client
ser=server
cc=gcc

serSrc=server.c comm.c
cliSrc=client.c comm.c

.PHONY:all
all:$(ser) $(cli)

$(ser):$(serSrc)
	$(cc) -o $@ $^
$(cli):$(cliSrc)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(cli) $(ser)


