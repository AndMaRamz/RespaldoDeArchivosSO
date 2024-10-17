.PHONY: run

MAIN=src/main.c
HEADERS=src/headers
PROCESS=src/process
FILES=child.c parent.c

run: $(MAIN) $(addsuffix $(PROCESS), $(FILES))
	gcc -o programa $(MAIN) -I $(HEADERS) $(addprefix $(PROCESS), $(FILES))