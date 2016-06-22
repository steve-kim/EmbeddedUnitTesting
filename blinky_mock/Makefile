UNITY_ROOT=/opt/Unity
CMOCK_ROOT=/opt/CMock

MOCK_OUT=./test/mocks

CC ?= gcc

CFLAGS=-Wall -g --coverage -mcmodel=medium

INC_DIRS=-I/opt/TivaWare-TMC4 -I./
TEST_INC=-I$(UNITY_ROOT)/src -I$(CMOCK_ROOT)/src -I/home/steve-kim/workspace/TivaWare-TMC4 -I./ -I./test/mocks -I./test

LIB_DIRS=-L/opt/TivaWare-TMC4/driverlib/gcc
TEST_LIBS=-L/home/steve-kim/workspace/TivaWare-TMC4/driverlib/gcc

LIBS=-ldriver

SYMBOLS=-DTEST

SRC_FILES=blinky.c led.c
#TEST_FILES=$(UNITY_ROOT)/src/unity.c test/TestBlinky.c test/test_runners/TestBlinky_Runner.c led.c
TEST_FILES=$(UNITY_ROOT)/src/unity.c $(CMOCK_ROOT)/src/cmock.c test/test_led.c test/test_runners/test_led_runner.c test/mocks/mock_mcu.c led.c

TARGET_EXTENSION=.out
TARGET_PRODUCTION=blinky
TARGET_TEST=blinky_test

all: clean default

unity.o: /home/steve-kim/workspace/CMock/vendor/unity/src/unity.c
	${CC} -o $@ -c $< -I /home/steve-kim/workspace/CMock/vendor/unity/src

cmock.o: /home/steve-kim/workspace/CMock/src/cmock.c
	${CC} -o $@ -c $< -I /home/steve-kim/workspace/CMock/vendor/unity/src -I /home/steve-kim/workspace/CMock/src

./test/mocks/mock_mcu.c: ./test/mcu.h
	@CMOCK_DIR=$(CMOCK_ROOT)
	@MOCK_OUT=$(MOCK_OUT) ruby $(CMOCK_ROOT)/scripts/create_mock.rb ./test/mcu.h

default:
	$(CC) $(CFLAGS) $(SYMBOLS) $(INC_DIRS) $(LIB_DIRS) $(SRC_FILES) $(LIBS) -o $(TARGET_PRODUCTION)$(TARGET_EXTENSION)

test: ./test/mocks/mock_mcu.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_led.c test/test_runners/test_led_runner.c
	$(CC) $(CFLAGS) $(SYMBOLS) $(TEST_INC) $(TEST_LIBS) $(TEST_FILES) $(LIBS) -o $(TARGET_TEST)$(TARGET_EXTENSION)
	./$(TARGET_TEST)$(TARGET_EXTENSION)

clean:
	rm -f *$(TARGET_EXTENSION) *.gc*

.PHONY: test

