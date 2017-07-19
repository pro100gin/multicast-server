IDIR = include
LDIR = lib
SDIR = src
LFLAGS = 
CFLAGS = -g -O2 -Wall -pedantic -ansi
CC = gcc

SUBDIRS = $(SDIR)
OBJSERV = $(SDIR)/server.o 
OBJCLIENT = $(SDIR)/client.o 


vpath %.c $(SDIR)
vpath %.o $(SDIR)
vpath %.h $(IDIR)

all: server client

server: $(OBJSERV)
		$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) 

$(OBJSERV): prepare

client: $(OBJCLIENT)
		$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) 


$(OBJCLIENT): prepare

.PHONY: prepare $(SUBDIRS)
prepare: $(SUBDIRS)

$(SUBDIRS):
		make -C $@
		
$(SDIR): $(LDIR)

clean:
		clear
		cd src	&& $(MAKE) clean
		rm -rf server client *.o
