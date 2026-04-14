NAME = ft_ssl
FILES = main.c \
			srcs/parsing.c \
			srcs/md5.c \
			srcs/sha256.c \
			srcs/utils.c
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(FILES) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

push:
	make fclean
	git -C .. add .
	git commit -m "$(MSG)"
	git push

.PHONY: all clean fclean re push
