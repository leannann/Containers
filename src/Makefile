G = gcc
WWW =  -Wall -Wextra -Wall -std=c++17 -lstdc++ -lgtest
GCOVFLAGS = -fprofile-arcs -ftest-coverage
TEST = s21_containers_test.cc
OUT = test
CLANG = clang-format -style=google


all: clean test gcov_report

gcov_report:
	$(G) $(WWW) $(GCOVFLAGS)  $(TEST) -o $(OUT)
	./$(OUT)
	lcov -t "test_html" -o unit_test.info -c -d .
	genhtml -o test_html unit_test.info
	open test_html/index.html


test: clean
	$(G) $(WWW) $(TEST) -o $(OUT)
	./$(OUT)

clean:
	rm -rf $(OUT) *.a *.gch *.gcno *.gcna *.gcda *.info *.dSYM test_html .qmake.stash

style_i:
	$(CLANG) -i *.h *.cc *.tpp

style_n: 
	$(CLANG) -n *.h *.cc *.tpp

valgrind:
	valgrind --leak-check=full --leak-resolution=med ./$(OUT)

leaks:
	leaks -atExit -- ./$(OUT)