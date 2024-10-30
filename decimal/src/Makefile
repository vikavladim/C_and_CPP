CC = gcc
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CHECK_STRING = -lcheck
endif
ifeq ($(UNAME), Linux)
CHECK_STRING = -lcheck -lm -lpthread -lrt -D_GNU_SOURCE -lsubunit
endif
CFLAGS = -Wall -Wextra -Werror -I $(SRC_DIR)
GCOV_FLAGS = --coverage
CLANG-FORMAT-PATH = ../materials/linters/.clang-format
TEST_PATH = tests
APP_LIB_PATH = vv_decimal.a
SRC_EXT = c
SRC_DIR = .
OBJ_DIR = .
GCOV_DIR = .
TEST_FILE = vv_decimal_test.c

APP_SOURCES = $(shell find $(SRC_DIR) -name '*.$(SRC_EXT)' ! -name '*test.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
TEST_SOURCES= $(shell find $(SRC_DIR) -name '*test.$(SRC_EXT))
TEST_OBJECTS = $(TEST_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)


.PHONY: all
all: clean $(APP_LIB_PATH) $(TEST_PATH) gcov_report


$(APP_LIB_PATH): $(APP_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(TEST_PATH): $(APP_SOURCES) $(TEST_FILE)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_FILE) $(APP_SOURCES) $(CHECK_STRING) -o $@

.PHONY: format
format:
	ls $(SRC_DIR)/*.c | xargs clang-format -i -style=file:$(CLANG-FORMAT-PATH);
	ls $(SRC_DIR)/*.h | xargs clang-format -i -style=file:$(CLANG-FORMAT-PATH);

.PHONY: test_format
test_format:
	ls $(SRC_DIR)/*.c | xargs clang-format -n -style=file:$(CLANG-FORMAT-PATH);
	ls $(SRC_DIR)/*.h | xargs clang-format -n -style=file:$(CLANG-FORMAT-PATH);

#https://21-school-by-students.notion.site/Homebrew-goinfre-af3acfc9cfee424481a8a08c204ff272
.PHONY: gcov_report
gcov_report: $(TEST_PATH)
	./tests; lcov -t "$(APP_PATH)" -o decimal.info -c -d .;
	genhtml -o report decimal.info;

# .PHONY: test
# test:
# 	make clean && make for_test

.PHONY: clean
clean:
	$(RM) decimal.info $(APP_LIB_PATH) $(TEST_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(SRC_DIR) -name '*.gcov' -exec $(RM) '{}' \;
	find $(SRC_DIR) -name '*.gcda' -exec $(RM) '{}' \;
	find $(SRC_DIR) -name '*.gcno' -exec $(RM) '{}' \;
	find $(SRC_DIR) -name '*.out' -exec $(RM) '{}' \;
	rm -rf report;

# for_test:
# # ifeq ("","$(wildcard ./check_vv_decimal.c)")
# # 	make check_mk
# # 	clang-format -i check_vv_decimal.c
# # endif
# 	gcc *.c $(CHECK_STRING) -o check_vv_decimal -lm
# 	./check_vv_decimal
# 	gcov -f check_vv_decimal

# check_mk:
# 	checkmk clean_mode=1 test/*.check > vv_decimal_test.c