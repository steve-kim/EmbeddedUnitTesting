UNITY_ROOT=/opt/Unity
CMOCK_ROOT=/opt/CMock

UNITY_DIR ?=/opt/Unity
MOCK_OUT ?=./test/mocks

CC=gcc

CFLAGS=-Wall -g --coverage -mcmodel=medium
#CFLAGS=-Wall -g -fprofile-arcs -ftest-coverage -mcmodel=medium -c

INC_DIRS=-I/opt/TivaWare-TMC4 -I./inc
TEST_INC=-I$(UNITY_ROOT)/src -I$(CMOCK_ROOT)/src -I../TivaWare-TMC4 -I./inc -I./test/mocks -I./test

LIB_DIRS=-L/opt/TivaWare-TMC4/driverlib/gcc
TEST_LIBS=-L../TivaWare-TMC4/driverlib/gcc

LIBS=-ldriver

SYMBOLS=-DTEST -DPART_TM4C123GH6PM

SRC_FILES=$(wildcard src/*.c)
TEST_FILES_ALL:=$(UNITY_ROOT)/src/unity.c $(CMOCK_ROOT)/src/cmock.c 
TEST_FILES_SRC=$(wildcard test/*.c)

FILES_TO_MOCK=$(wildcard inc/*.h)

TARGET_EXTENSION=.out

all: clean default

./test/mocks/mock_mcu.c: ./test/mcu.h
	@CMOCK_DIR=${CMOCK_ROOT} ruby $(CMOCK_ROOT)/scripts/create_mock.rb ./test/mcu.h

create_mocks:
	$(foreach mock, $(FILES_TO_MOCK), CMOCK_DIR=${CMOCK_ROOT} ruby $(CMOCK_ROOT)/scripts/create_mock.rb $(mock);)

test_humidity:
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb ./test/test_humidity.c ./test/test_runner/test_humidity_runner.c
	$(CC) $(CFLAGS) $(SYMBOLS) $(TEST_INC) $(TEST_LIBS) $(TEST_FILES_ALL) ./test/test_humidity.c ./src/humidity.c ./test/mocks/mock_mcu.c ./test/mocks/mock_i2c_interface.c ./test/test_runner/test_humidity_runner.c $(LIBS) -o humidity_test$(TARGET_EXTENSION)

test_led:
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb ./test/test_led.c ./test/test_runner/test_led_runner.c
	$(CC) $(CFLAGS) $(SYMBOLS) $(TEST_INC) $(TEST_LIBS) $(TEST_FILES_ALL) ./test/test_led.c ./src/led.c ./test/mocks/mock_mcu.c ./test/test_runner/test_led_runner.c $(LIBS) -o led_test$(TARGET_EXTENSION)

test_timer:
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb ./test/test_timer.c ./test/test_runner/test_timer_runner.c
	$(CC) $(CFLAGS) $(SYMBOLS) $(TEST_INC) $(TEST_LIBS) $(TEST_FILES_ALL) ./test/test_timer.c ./src/timer.c ./src/led.c ./test/mocks/mock_mcu.c ./test/mocks/mock_humidity.c ./test/test_runner/test_timer_runner.c $(LIBS) -o timer_test$(TARGET_EXTENSION)

test: ./test/mocks/mock_mcu.c create_mocks test_humidity test_led test_timer
	@echo "\n\nExecuting unit tests...\n"
	./humidity_test.out
	@echo "\n"
	./led_test.out
	@echo "\n"
	./timer_test.out

clean:
	rm *$(TARGET_EXTENSION) *.gc* ./test/mocks/* ./test/test_runner/*

print:
	echo $(SRC_FILES)
	echo $(TEST_FILES_SRC)
	echo $(TEST_FILES_ALL)
	echo $(FILES_TO_MOCK)

.PHONY: test
