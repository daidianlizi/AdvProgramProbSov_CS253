main: main.cpp
	@echo     ------------compiling main.cpp to create executable program main----------------
	gcc -ggdb -std=c++11 -c main.cpp reset.cpp
	gcc -o urlParse main.o reset.o
	@echo     ------------Congratulation to you! Successfully compile.
	@echo     ------------Run manually by :
	@echo     ------------"./urlParse < urltest.txt"
clean:
	rm -rf urlParse urlParse.dSYM urlParse.o reset.o 