CC := gcc
CFLAGS = -std=gnu17 -g -Wall -Wextra -Wno-missing-field-initializers
CPPFLAGS := -I. -Isorts
LDFLAGS := -g

srcs := $(wildcard sorts/*.c) test.c
objs := $(srcs:%=out/%.o)

.PHONY: all
all: test

test: $(objs)
	$(CC) $(objs) -o $@ $(LDFLAGS)

out/%.c.o: %.c test.h config.h
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf out test
