VFS: main.o vfs.o 
	g++ main.o vfs.o -o VFS


vfs.o: vfs.h vfs.cpp
	g++ -c vfs.cpp

main.o: main.cpp 
	g++ -c main.cpp

clean:
	rm *.o VFS