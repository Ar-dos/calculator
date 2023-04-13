CFLAGS=-Wall -Wextra -Werror -std=c++17
LFLAGS = -lgtest --coverage

all: install gcov_report

install:
	qmake View/calc.pro -o View/Makefile
	make -C View
	mv View/calc.app .
	rm -rf View/moc_calc.cpp View/Makefile View/ui_calc.h View/*.o .qmake.stash View/.qmake.stash View/.qtc_clangd

uninstall:
	rm -rf calc.app

dvi:
	# brew install doxygen
	doxygen conf.conf
	open doc/html/index.html

dist: install
	tar -cf calc.tar calc.app

clean:
	rm -rf View/*.o *.gcno *.gcda *.gcov *.info *.tar report *.c *.h test calc.app html latex

test:
	g++ $(CFLAGS) calc/test.cpp calc/Model/parser.cpp -o test $(LFLAGS)
	./test --enable-coverage

style:
	find -iname *.h -o -iname *.cpp | xargs clang-format -n

gcov_report: test
	lcov -c -d . -t test -o test.info
	genhtml -o report test.info
	open report/index.html


