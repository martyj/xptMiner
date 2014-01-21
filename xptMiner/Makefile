CXX = g++
CFLAGS = -mtune=native -Wall -Wextra -std=c++0x -O3 -fomit-frame-pointer

OSVERSION := $(shell uname -s)
LIBS = -lgmp -lgmpxx -lcrypto -lssl -pthread

ifeq ($(OSVERSION),Linux)
	LIBS += -lrt
endif

# You might need to edit these paths too
LIBPATHS = -L/usr/local/lib -L/usr/lib
INCLUDEPATHS = -I/usr/local/include -I/usr/include -IyxptMiner/includes/

ifeq ($(OSVERSION),Darwin)
	GOT_MACPORTS := $(shell which port)
ifdef GOT_MACPORTS
	LIBPATHS += -L/opt/local/lib
	INCLUDEPATHS += -I/opt/local/include
endif
endif

JHLIB = jhlib/customBuffer.o \
	jhlib/fastString_eprintf.o \
	jhlib/packetBuffer.o \
	jhlib/fastString.o \
	jhlib/hashTable_uint32.o \
	jhlib/simpleList.o \
	jhlib/simpleHTTP.o

OBJS = \
	jhlib/customBuffer.o \
	jsonBuilder.o \
	jsonClient.o \
	jsonObject.o \
	jsonParser.o \
	jsonrpc.o \
	main.o \
	metiscoinMiner.o \
	primecoinMiner.o \
	protosharesMiner.o \
	script.o \
	scriptMinerCPU.o \
	sha2.o \
	ticker.o \
	transaction.o \
	xptClient.o \
	xptClientPacketHandler.o \
	xptPacketbuffer.o \
	xptServer.o \
	xptServerPacketHandler.o

all: jhmetisminer

xptMiner/%.o: xptMiner/%.cpp
	$(CXX) -c $(CFLAGS) $(INCLUDEPATHS) $< -o $@

jhmetisminer: $(OBJS:xptMiner/%=xptMiner/%) $(JHLIB:xptMiner/jhlib/%=xptMiner/jhlib/%)
	$(CXX) $(CFLAGS) $(LIBPATHS) $(INCLUDEPATHS) -o $@ $^ $(LIBS)

clean:
	-rm -f jhmetisminer
	-rm -f xptMiner/*.o
	-rm -f xptMiner/jhlib/*.o

