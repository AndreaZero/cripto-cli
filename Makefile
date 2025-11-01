# Makefile for crypto-cli

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS = -lcurl -lcjson

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/crypto

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(OBJDIR) $(BINDIR)

# Build target
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install (copy binary to /usr/local/bin)
install: $(TARGET)
	@echo "Installing crypto-cli to /usr/local/bin..."
	@sudo cp $(TARGET) /usr/local/bin/crypto
	@sudo chmod +x /usr/local/bin/crypto
	@echo "✓ Installed! You can now use 'crypto' from anywhere."

# Uninstall
uninstall:
	rm -f /usr/local/bin/crypto

# Development target with debug symbols
debug: CFLAGS += -g -DDEBUG
debug: all

# Check for required libraries
check-deps:
	@pkg-config --exists libcurl && echo "✓ libcurl found" || echo "✗ libcurl not found"
	@pkg-config --exists libcjson && echo "✓ libcjson found" || echo "✗ libcjson not found"

.PHONY: all directories clean install uninstall debug check-deps

