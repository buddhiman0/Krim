exec = krim.out
sources = $(wildcard src/*.c) 
objects = $(sources:.c=.o)
flags = -g


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: src/%.c include/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out 
	-rm *.o
	-rm src/*.o


run:
	./krim.out

install:
	cp ./krim.out /usr/local/bin/krim


