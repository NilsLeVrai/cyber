#pragma once

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

typedef struct s_hash_parsing {
	int		flag_p;
	int		flag_q;
	int		flag_r;
	char	**strings;
	int		nb_strings;
	char	**files;
	int		nb_files;
} t_hash_parsing;

typedef struct	s_command {
	char	*name;
	void	(*func)(t_hash_parsing *);
} t_command;

void dispatcher(char *argv, t_hash_parsing *parsing);
void check_parsing(int argc, char **argv, t_hash_parsing *parsing);
void free_parsing(t_hash_parsing *parsing);