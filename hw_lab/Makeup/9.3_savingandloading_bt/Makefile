main: main.cpp
	@echo     ------------compiling main.cpp to create executable program main----------------
	g++  -ggdb   -std=c++11   main.cpp   -o   main
	@echo     ------------Congratulation to you! Successfully compile.
	@echo     ------------Run manually by :
	@echo     ------------"./main load.txt save.txt"

all: solution

solution:
	g++  -ggdb   -std=c++11   main.cpp   -o   main
	./main load1.txt save1.txt
	./main load2.txt save2.txt
	./main load3.txt save3.txt

clean:
	rm main save1.txt save2.txt save3.txt