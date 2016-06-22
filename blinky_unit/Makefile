UNITY_ROOT=/opt/Unity
CC=gcc

CFLAGS=-Wall -g --coverage -mcmodel=medium

INC_DIRS=-I/opt/TivaWare-TMC4 -I./
TEST_INC=-I$(UNITY_ROOT)/src -I/home/steve-kim/workspace/EmbeddedUnitTesting/TivaWare-TMC4 -I./

LIB_DIRS=-L/opt/TivaWare-TMC4/driverlib/gcc
TEST_LIBS=-L/home/steve-kim/workspace/EmbeddedUnitTesting/TivaWare-TMC4/driverlib/gcc

LIBS=-ldriver

SYMBOLS=-DTEST

SRC_FILES=blinky.c led.c
TEST_FILES=$(UNITY_ROOT)/src/unity.c test/TestBlinky.c test/test_runners/TestBlinky_Runner.c led.c

TARGET_EXTENSION=.out
TARGET_PRODUCTION=blinky
TARGET_TEST=blinky_test

all: clean default

default:
	$(CC) $(CFLAGS) $(SYMBOLS) $(INC_DIRS) $(LIB_DIRS) $(SRC_FILES) $(LIBS) -o $(TARGET_PRODUCTION)$(TARGET_EXTENSION)

test:
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/TestBlinky.c test/test_runners/TestBlinky_Runner.c
	$(CC) $(CFLAGS) $(SYMBOLS) $(TEST_INC) $(TEST_LIBS) $(TEST_FILES) $(LIBS) -o $(TARGET_TEST)$(TARGET_EXTENSION)

clean:
	rm -f *$(TARGET_EXTENSION) *.gc*

.PHONY: test
