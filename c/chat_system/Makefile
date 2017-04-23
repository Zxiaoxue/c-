ROOT_PATH=$(shell pwd)
SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
COMM_PATH=$(ROOT_PATH)/comm
LOG_PATH=$(ROOT_PATH)/log
LIB_PATH=$(ROOT_PATH)/lib
WINDOW_PATH=$(RPPT_PATH)/window
CONF_PATH=$(ROOT_PATH)/conf

CC=g++

SERVER_SRC=$(shell ls $(SERVER_PATH) | egrep -v '.*\.h' | egrep '.*\.cpp')
CLIENT_SRC=$(shell ls $(CLIENT_PATH) | egrep -v '.*\.h' | egrep '.*\.cpp')

SERVER_BIN=Server
CLIENT_BIN=Client

SERVER_OBJ=$(shell echo $(SERVER_SRC) | sed 's/\.cpp/\.o/g')
CLIENT_OBJ=$(shell echo $(CLIENT_SRC) | sed 's/\.cpp/\.o/g')

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	$(CC) -o $@ $^
%.o:$(SERVER_PATH)/%.cpp
	$(CC) -c $<
$(CLIENT_BIN):$(CLIENT_OBJ)
	$(CC) -o $@ $^
%.o:$(CLIENT_PATH)/%.cpp
	$(CC) -c $<

.PHONY:clean
clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN) $(SERVER_OBJ) $(CLIENT_OBJ)

.PHONY:debug
debug:
	@echo $(SERVER_SRC)
	@echo $(CLIENT_SRC)
	@echo $(SERVER_PATH)
	@echo $(CLIENT_PATH)

