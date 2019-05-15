.PHONY: run
run: main
	@echo Testcase 1, expected result is:  2 numbers, average 2.
	valgrind ./average ./TestCases/file1.dat

	@echo Testcase 2, expected result is:  3 numbers, average 20.
	valgrind ./average ./TestCases/file2.dat

	@echo Testcase 3, expected result is:  1 numbers, average -1.
	valgrind ./average ./TestCases/file3.dat

	@echo Testcase 4, expected result is:  no data in input file.
	valgrind ./average ./TestCases/file4.dat

	@echo Testcase 5, expected result is:  2 numbers, average -23.
	valgrind ./average ./TestCases/file5.txt

	@echo Testcase 6, expected result is:  no input of the file name.
	valgrind ./average

	@echo Testcase 7, expected result is:  wrong file name, cannot open file.
	valgrind ./average wrong_name_file.dat

	@echo Testcase 8, instructor\'s example, expected result is:  1000 numbers, average -0.0421152.
	valgrind ./average ./TestCases/standardTestInput.txt

	@echo Congratulation, all done!
	
main: main.cpp
	@echo     ------------compiling main.cpp to create executable program main----------------
	g++  -ggdb   -std=c++11   main.cpp   -o   average
	@echo     ------------Congratulation to you! Successfully compile.Use \"./average [file]\" to calculate, for example:
	@echo     ------------'./average ./TestCases/file1.dat'
	@echo     ------------To run all my test cases, use: \"make run\".

