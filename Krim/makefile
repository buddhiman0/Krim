exec = krim
sources = $(wildcard *.c)
objects = $(sources:.c=.o)
flags = -g -Wno-switch -Wno-return-type 


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c %.h
	gcc -c $(flags) $< -o $@
#
#run:
#	make

build:
	make
	
install:
	make clean
	make
	cp ./krim /usr/local/bin/kk
	clear
	kk /Users/ashokpaudel/Documents/Krim/Krim/test.k

run:
	./krim test.k
clean:
	-rm -f *.out
	-rm -f *.o
	
all:
	sudo make install
	
