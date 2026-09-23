AS      = nasm
CXX     = gcc
LD      = ld
RM      = rm -f
ASFLAGS	= -g -f elf64

NAME    = Colleen
SOURCES    = Colleen.s
OBJECTS    = $(SOURCES:.s=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CXX) $(OBJECTS) -o $(NAME)

%.o: %.c
	@$(AS) $(ASFLAGS) $< -o $@ 

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) outfile output

re: fclean all

test:
	make re
	./$(NAME) > output
	diff output Colleen.c
	rm output

nils: fclean
	cd .. && git add . && git commit -m "update" && git push

.PHONY: all clean fclean re nils test
