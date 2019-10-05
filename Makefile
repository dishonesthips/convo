CC = gcc       # compiler
CFLAGS = -Wall -g -std=c99 # compilation flg 
LD = gcc       # linker

TARGETS= convo 

all: ${TARGETS}

findpng: convo.o 
	$(LD) -o $@ $^ $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

.PHONY: clean
clean:
	rm -f *.d *.o $(TARGETS) 

