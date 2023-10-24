CXX= g++
CXXFLAGS= -std=c++17 -g -Wall -Werror -Wextra
GTESTFLAGS = -lgtest -pthread

MAINSRC= main.cc
SRC= $(wildcard model/*.h model/*.cc controller/*.h)
TESTSRC = tests/test.cc
ALLFILES= $(wildcard *.cc *.h)
EXECUTABLE= calc
TESTEXEC = a.out

Vgrind= CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes -v --verbose -q --quiet -s

all: dvi clean install test gcov_report open

clean:
	rm -rf $(EXECUTABLE) $(TESTEXEC)
	rm -rf */*.gch
	rm -rf *.gcda *.gcno report test.info *.o


test: clean $(TESTEXEC)
	./$(TESTEXEC)
	leaks -atExit -- ./$(TESTEXEC)
	rm $(TESTEXEC)

$(TESTEXEC):
	$(CXX) $(SRC) $(TESTSRC) $(CXXFLAGS) $(GTESTFLAGS)

install:
	mkdir -p ./../../SmartCalc
	cd view && qmake && make && make clean && rm -rf Makefile && mv s21_SmartCalc.app ./../../../SmartCalc
	./../../SmartCalc/Contents/MacOS/s21_SmartCalc

open:
	./../../SmartCalc/Contents/MacOS/s21_SmartCalc

uninstall:
	rm -rf ./../../SmartCalc

main:
	$(CXX) $(SRC) $(MAINSRC) -o $(EXECUTABLE) $(CXXFLAGS)
	leaks -atExit -- ./$(EXECUTABLE)

dvi:
	open Instruction_SmartCalc.md

dist:
	rm -rf ../Archive_SmartCalc_v2_0/
	mkdir ../Archive_SmartCalc_v2_0
	mkdir ../Archive_SmartCalc_v2_0/src
	cp -r ../src/* ../Archive_SmartCalc_v2_0/src
	tar cvzf ./../../SmartCalcApp_v2_0.tgz ../Archive_SmartCalc_v2_0/
	zip -r ./../../SmartCalc_v2_0.zip ../Archive_SmartCalc_v2_0/
	rm -rf ../Archive_SmartCalc_v2_0

gcov_report: clean
	$(CXX) --coverage $(SRC) $(TESTSRC) -o $(TESTEXEC) $(CXXFLAGS)  $(GTESTFLAGS)
	./$(TESTEXEC)
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open ./report/index.html

style:
	cp ../materials/linters/.clang-format .
	clang-format -i $(ALL_FILES) */*.h */*.cc
	rm -f .clang-format

check:
	$(pwd)
	cp ../materials/linters/.clang-format .
	clang-format -n $(ALL_FILES) */*.h */*.cc
	rm -f .clang-format