NAME = Colleen

CXX = cc
CXXFLAGS = -Wall -Werror -Wextra
INCLUDES = -I ./includes/

SRC_DIR = .
SOURCES = Colleen.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

push:
	make fclean
	git -C .. add .
	git commit -m "$(MSG)"
	git push

test:
	make re
	./$(NAME) > output
	diff output Colleen.c 
	rm output

.PHONY: all clean fclean re push test
