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

nils: fclean
	cd .. && git add . && git commit -m "update" && git push

.PHONY: all clean fclean re nils
