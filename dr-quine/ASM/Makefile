AS    = nasm
LD      = ld
RM      = rm -f
ASFLAGS	= -f elf64

NAME    = Colleen
SRCS    = Colleen.s
OBJS    = $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(LD) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
