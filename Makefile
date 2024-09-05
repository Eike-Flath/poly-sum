CC ?= gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O2 -march=native -s
LD = $(CC)
LDFLAGS = -s
LIBS = -lgmp

OUT = poly-sum
SRC = poly-sum.c

# End of configuration

OBJ = $(SRC:.c=.o)

$(OUT): $(OBJ)
	$(LD) $(LDFLAGS) -o "$@" $^ $(LIBS)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -o "$@" -c "$<"

.PHONY: clean
clean:
	@rm -fv "$(OUT)" $(OBJ) || true

