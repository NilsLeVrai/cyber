AS    = nasm
LD      = ld
RM      = rm -f
ASFLAGS	= -g -f elf64

NAME    = Colleen
SRCS    = Colleen.s
OBJS    = $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

push:
	make fclean
	git -C .. add .
	git commit -m "$(MSG)"
	git push

test:
	make re
	./$(NAME) > output
	diff output Colleen.s
	rm output

.PHONY: all clean fclean re push test
