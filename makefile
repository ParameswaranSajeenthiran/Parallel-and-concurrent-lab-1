# Makefile for Lab project with optional taskset core binding

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pthread -D_XOPEN_SOURCE=700
LDFLAGS = -lm -pthread

# Source files
SRC = main.c \
      linkedList.c \
      tests/Serial.c \
      tests/Config.c \
      tests/Mutex.c \
      tests/ReadWriteLock.c

# Header files
HEADERS = linkedList.h \
          tests/Serial.h \
          tests/Config.h \
          tests/Mutex.h \
          tests/Constants.h \
          tests/ReadWriteLock.h

# Output executable
TARGET = Lab

# Default build
all: $(TARGET)

# Build executable
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Run program (usage: make run CORES=n)
run: $(TARGET)
ifeq ($(OS),Windows_NT)
	@echo "Running $(TARGET) on Windows"
	./$(TARGET).exe
else
ifneq ($(CORES),)
	@echo "Running $(TARGET) on Linux with cores 0-$(shell echo $$(($(CORES)-1)))"
	taskset -c 0-$(shell echo $$(($(CORES)-1))) ./$(TARGET)
else
	@echo "Running $(TARGET) on Linux using all cores"
	./$(TARGET)
endif
endif

# Clean build
clean:
	rm -f $(TARGET) *.o
