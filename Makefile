CC := gcc
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic
CPPFLAGS := -Idomus/src -Idomus/src/scan -Idomus/src/token

TARGET := domus.exe
SOURCES := domus/src/MAIN.c domus/src/scan/SCAN.c
HEADERS := domus/src/GLOBALS.h domus/src/scan/SCAN.h domus/src/token/TOKENS.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	cmd /C "if exist $(TARGET) del /Q $(TARGET)"
