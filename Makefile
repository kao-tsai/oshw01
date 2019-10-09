all:	simulate

simulate:	main.o
						g++	-ggdb	-o	simulate	main.o
main.o:	main.cpp
						g++	-ggdb	-c	main.cpp
dep:
						echo "Do nothing"
clean:
						rm	-f	main*.o