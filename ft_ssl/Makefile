NAME = ft_ssl
FILES = main.c \
			srcs/parsing.c \
			srcs/md5.c \
			srcs/sha256.c
CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(FILES) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all

push:
	git add .
	git commit -m "$(MSG)"
	git push

.PHONY: all clean fclean re push
