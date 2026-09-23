NAME = Colleen

CXX = cc
CXXFLAGS = -Wall -Werror -Wextra
INCLUDES = -I ./includes/

SRC_DIR = .
SOURCES = Grace_kid.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDES)

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