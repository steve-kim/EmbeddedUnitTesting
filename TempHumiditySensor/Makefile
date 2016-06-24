UNITY_ROOT=/opt/Unity
CMOCK_ROOT=/opt/CMock

UNITY_DIR ?=/opt/Unity
MOCK_OUT ?=./test/mocks

CC=gcc

CFLAGS=-Wall -g --coverage -mcmodel=medium

INC_DIRS=-I/opt/TivaWare-TMC4 -I./inc
TEST_INC=-I$(UNITY_ROOT)/src -I$(CMOCK_ROOT)/src -I../TivaWare-TMC4 -I./inc -I./test/mocks -I./test

LIB_DIRS=-L/opt/TivaWare-TMC4/driverlib/gcc
TEST_LIBS=-L../TivaWare-TMC4/driverlib/gcc

LIBS=-ldriver

SYMBOLS=-DTEST -DPART_TM4C123GH6PM

SRC_FILES=$(wildcard src/*.c)
TEST_FILES_ALL:=$(UNITY_ROOT)/src/unity.c $(CMOCK_ROOT)/src/cmock.c test/*.c test/mocks/*.c test/test_runner/*.c $(filter-out src/main.c, $(SRC_FILES))
TEST_FILES_SRC=$(wildcard test/*.c)

FILES_TO_MOCK=$(wildcard inc/*.h)

TARGET_EXTENSION=.out
TARGET_PRODUCTION=motor_control
TARGET_TEST=motor_test

all: clean default

unity.o: $(UNITY_ROOT)/src/unity.c
	${CC} -o $@ -c $< -I $(UNITY_ROOT)/src

cmock.o: $(CMOCK_ROOT)/src/cmock.c
	${CC} -o $@ -c $< -I $(UNITY_ROOT)/src -I $(CMOCK_ROOT)/src

./test/mocks/mock_mcu.c: ./test/mcu.h
	@CMOCK_DIR=${CMOCK_ROOT} ruby $(CMOCK_ROOT)/scripts/create_mock.rb ./test/mcu.h

create_mocks:
	$(foreach mock, $(FILES_TO_MOCK), CMOCK_DIR=${CMOCK_ROOT} ruby $(CMOCK_ROOT)/scripts/create_mock.rb $(mock);)

test: ./test/mocks/mock_mcu.c create_mocks
	$(foreach src, $(TEST_FILES_SRC), ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(src) test/test_runner/$(notdir $(basename $(src)))_runner.c;)
	$(CC) $(CFLAGS) $(SYMBOLS) $(TEST_INC) $(TEST_LIBS) $(TEST_FILES_ALL) $(LIBS) -o $(TARGET_TEST)$(TARGET_EXTENSION)

print:
	echo $(SRC_FILES)
	echo $(TEST_FILES_SRC)
	echo $(TEST_FILES_ALL)
	echo $(FILES_TO_MOCK)

.PHONY: test
