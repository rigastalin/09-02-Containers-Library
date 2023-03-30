.PHONY: all clean check rebuild test gcov_report

CC := g++
STD := -std=c++17 -g
CFLAGS := -Wall -Werror -Wextra
GFLAGS := -fprofile-arcs -ftest-coverage
REPORTDIR := report
GCOV := --coverage
OS := $(shell uname -s)

SOURCES= s21_queue.cpp

OBJECTS := $(SOURCES:.cpp=.o)

ifeq ($(OS), Linux)
  LIBS := -lgtest -lpthread -lrt -lm
  LEAKER := valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes -s --quiet
else 
  LIBS := -lgtest
  LEAKER := CK_FORK=no leaks --atExit --
endif

all: clean test

############################## -> LIBRARY <- ############################
s21_containers.a:
	$(CC) $(STD) -c $(SOURCES) -o s21_queue.o
	ar rcs s21_containers.a $(OBJECTS)

############################## -> TESTS <- ##############################
test: s21_containers.a
	$(CC) $(STD) $(GCOV) -c $(SOURCES) $(LIBS)
	$(CC) -c s21_test.cpp $(STD)
	$(CC) s21_test.o s21_containers.a $(LIBS) -o testing
	$(CC) -O0 $(STD) $(CFLAGS) s21_test.cpp $(SOURCES) $(LIBS) $(GFLAGS) -o testing
	./testing

############################## -> LEAKS <- ##############################
leaks:
	$(LEAKER) ./testing

############################## -> REPORT <- ##############################
gcov_report:
	lcov -t "Unit-tests of s21_containers" -o s21_containers.info -c -d . --no-external
	genhtml -o $(REPORTDIR) s21_containers.info
	open -a "Google Chrome" $(REPORTDIR)/index.html


##############################  -> CHECK <- ##############################
check:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i *.cpp *.h
	@rm -rf .clang-format

##############################  -> CLEAN <- ##############################
clean:
	rm -rf report *.o testing test *.out *.gcov *.gcda *.gcno *.info *.a *.dSYM *.gch
	rm -rf *.a.*
