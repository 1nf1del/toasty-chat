SERVER_DIR=server
CLIENT_DIR=client

CLEAN=$(MAKE) clean

all:
	$(MAKE) -C $(SERVER_DIR)
	$(MAKE) -C $(CLIENT_DIR)

clean:
	+$(CLEAN) -C $(SERVER_DIR)
	+$(CLEAN) -C $(CLIENT_DIR)