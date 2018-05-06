# Specific part of the Makefile
EXEC=main
# Begin generic part of the Makefile
CC=gcc
CFLAGS= -Wextra -Wall -std=c99
LDFLAGS=
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: $(EXEC)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o
mrproper: clean
	@rm -rf $(EXEC)
# End generic part of the makefile
# List of target
main.o: sha256.h sha256_utils.h Transaction.h block.h blockchain.h cheater.h
