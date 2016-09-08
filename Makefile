TARGET = filesearch

all: $(TARGET)
	
clean:
	rm -rf $(TARGET) *.o
main.o: main.c
	gcc -O2 -c -o main.o main.c
btreeindex.o: btreeindex.c
	gcc -O2 -c -o btreeindex.o btreeindex.c
$(TARGET): main.o btreeindex.o
	gcc -O2 -o $(TARGET) main.o btreeindex.o

