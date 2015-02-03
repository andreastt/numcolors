.PHONY: all clean
all: numcolors.o getcolors

%.o: %.c
	cc -o $@ -c $^

getcolors: getcolors.c numcolors.o
	cc -o $@ $^ -ltermcap

clean:
	rm -f getcolors numcolors.o
