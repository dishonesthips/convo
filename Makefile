CC = gcc       # compiler
CFLAGS = -Wall -std=c99 # compilation flg 
LD = gcc       # linker

TARGETS = convo 

all: ${TARGETS}

debug: CFLAGS += -DDEBUG -g
debug: ${TARGETS}


convo: convo.o 
	$(LD) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

.PHONY: clean
clean:
	rm -f *.d *.o $(TARGETS) 

