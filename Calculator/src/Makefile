CC = g++ -std=c17  
CFLAGS = -Wall -Wextra -Werror 
FLAGS_TEST = -coverage -lcheck -lm

SOURCE_FILES = SmartCalc2_0/model/**/*.cc
TEST_FILES = test/*.cc
OBJECT_FILES = $(SOURCE_FILES:.c=.o) $(TEST_FILES:.c=.o)

ifeq ($(shell uname -s),Linux)
	FLAGS_TEST += -lpthread -lrt -lsubunit
endif

.PHONY: all test clean for_test install uninstall valgrind install dist dvi gcov_report

all: test gcov_report dist dvi install
	./build/Calculator

for_test: $(OBJECT_FILES) 
	$(CC)  $(TEST_FILES) -o check_vv_smart_calc $(FLAGS_TEST)
	./check_vv_smart_calc
	gcov -f check_vv_smart_calc

%.o: %.cc
	$(CC) $(CFLAGS) -c $^ -o $@

test: clean
	# if [ !  -d SmartCalc2_0/external/googletest ]; then\
	# 	git clone https://github.com/google/googletest.git SmartCalc2_0/external/googletest;\
	# fi
	cmake -S SmartCalc2_0 -B test -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc
	cmake --build test --target test_app
	./test/test_app
	gcov -f test/test_app

format:
	cp ../materials/linters/.clang-format .
	# test/*.cc 
	clang-format -i SmartCalc2_0/model/*/*.cc SmartCalc2_0/model/*/*.h SmartCalc2_0/*.cc SmartCalc2_0/controller/*.h SmartCalc2_0/controller/*.cc *.cc
	rm -rf .clang-format

style_test:
	cp ../materials/linters/.clang-format .
	clang-format -n test/*.cc SmartCalc2_0/model/**/*.cc SmartCalc2_0/model/**/*.h *.cc controller/*.h controller/*.cc 
	rm -rf .clang-format

#https://21-school-by-students.notion.site/Homebrew-goinfre-af3acfc9cfee424481a8a08c204ff272
gcov_report: test
	mkdir report
	# lcov -d ./SmartCalc2_0/model/calculator --capture -o report.info 
	# lcov -d ./ --capture -o report.info --exclude *include* --exclude "*src*" 
	lcov -d ./ --capture -o report.info --exclude *include* --exclude "*/test/*" 
	# lcov -d ./ --capture -o report.info --exclude "*/*" 
	genhtml -o report report.info 
	open report/index.html
	
clean: uninstall
	rm -rf ../build test/ ../.cmake ../.qtc_clangd ../.vscode ../CMakeFiles ../smartcalc* ../Testing ../CMake* ../cmake* ../qtcsettings* ../Make* ../src/CMakeLists.txt.*
	rm -rf report *.gcno *.gcda *.gcov *.o check_vv_smart_calc *.info *.a *.out SmartCalc_v1.0.tgz .DS_Store ../.DS_Store #CMakeLists.users
	rm -rf googletest test SmartCalc2_0/external/googletest SmartCalc2_0/googletest
	rm -rf SmartCalc2_0/CMakeLists.txt.user
	rm -rf SmartCalc_v2.0.*

valgrind: test
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./check_vv_smart_calc

p: clean format
	git add .
	git commit -m "work"
	git push

install:
	cmake -S SmartCalc2_0 -B build 
	cmake --build build --target SmartCalc2_0
	./build/SmartCalc2_0

uninstall:
	rm -rf build*

dvi:
	# doxygen
	open doxygen/index.html

dist: clean
	tar -czf SmartCalc_v2.0.tgz ./*
	# zip -r SmartCalc_v2.0.zip ./*
