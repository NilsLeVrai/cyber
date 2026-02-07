NAME = ft_ssl
FILES = main.c
CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(FILES) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
