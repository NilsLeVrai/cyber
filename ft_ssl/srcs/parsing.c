#include "../includes/ft_ssl.h"
#include <stdio.h> //debug

static t_command commands[] = {
	{"md5", ft_md5},
	{"sha256", ft_sha256},
	{NULL, NULL}
};

void init_parsing(t_hash_parsing *parsing) {
	parsing->flag_p = 0;
	parsing->flag_q = 0;
	parsing->flag_r = 0;
	parsing->strings = NULL;
	parsing->nb_strings = 0;
	parsing->files = NULL;
	parsing->nb_files = 0;
	return;
}

void	dispatcher(char *command, t_hash_parsing *parsing) {
	int i;

	i = 0;
	while (commands[i].name != NULL) {
		if (ft_strcmp(command, commands[i].name) == 0) {
			commands[i].func(parsing);
			return ;
		}
		i++;
	}
}

static void add_file(t_hash_parsing *parsing, char *argv, int *err) {

	char	**old;
	int		i;
	int		file;

	file = open(argv, O_RDONLY);
	if (file == -1) {
		*err = errno;
		return ;
	}
	close(file);
	old = parsing->files;
	i = 0;
	parsing->files = malloc(sizeof(char *) * (parsing->nb_files + 1));
	if (!parsing->files) {
		printf("alloc failed\n");
		return;
	}
	while (i < parsing->nb_files) {
		parsing->files[i] = old[i];
		i++;
	}
	free(old);
	parsing->files[parsing->nb_files] = argv;
	parsing->nb_files++;
}

static void add_string(t_hash_parsing *parsing, char *str) {

	int		i;
	char	**old;

	i = 0;
	old = parsing->strings;
	parsing->strings = malloc(sizeof(char *) * (parsing->nb_strings + 1));
	if (!parsing->strings) {
		printf("alloc failed\n");
		return;
	}
	while (i < parsing->nb_strings) {
		parsing->strings[i] = old[i];
		i++;
	}
	parsing->strings[parsing->nb_strings] = str;
	free(old);
	parsing->nb_strings++;
}

void check_parsing(int argc, char **argv, t_hash_parsing *parsing) {

	int		err;

	err = 0;
	if (argc < 2)
		write(1, "Usage\n", 6); // change write usage
	init_parsing(parsing);
	for (int i = 2; i < argc; i++) {
		if (argv[i][0] == '-') {
			for (int j = 1; argv[i][j] != '\0'; j++) {
				switch (argv[i][j])
				{
					case 'p':
						parsing->flag_p = 1;
						break;
					case 'q':
						parsing->flag_q = 1;
						break;
					case 'r':
						parsing->flag_r = 1;
						break;
					case 's':
						if (i + 1 < argc) {
							add_string(parsing, argv[i + 1]);
							i++;
						} else {
							printf("no string after -s\n");
						}
						break;
					default:
						break;
				}
			}
		} else {
			add_file(parsing, argv[i], &err);
			if (err) {
				write_error(argv[i], &err);
				err = 0;
			}
		}
	}
	return;
}