#include "../includes/ft_ssl.h"

#define USAGE_MSG "ft_ssl: usage: ft_ssl command [flags] [file/string]\n"
#define NO_ARG_S_MSG "ft_ssl: -s: option requires an argument\n"

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

void	free_parsing(t_hash_parsing *parsing) {
	free(parsing->strings);
	free(parsing->files);
}

int	dispatcher(char *argv, t_hash_parsing *parsing) {
	int		i;
	int		status;
	char	*command;

	i = 0;
	command = to_lower(argv);
	if (!command) {
		write_error(NULL, NULL, errno);
		free_parsing(parsing);
		return (EXIT_FAILURE);
	}
	while (commands[i].name != NULL) {
		if (ft_strcmp(command, commands[i].name) == 0) {
			status = commands[i].func(parsing);
			free(command);
			free_parsing(parsing);
			return (status);
		}
		i++;
	}
	write(2, "ft_ssl: Error: '", 16);
	write(2, argv, ft_strlen(argv));
	write(2, "' is an invalid command.\n", 25);
	free(command);
	free_parsing(parsing);
	return (EXIT_FAILURE);
}

static void add_file(t_hash_parsing *parsing, char *argv) {

	char	**old;
	int		i;

	old = parsing->files;
	i = 0;
	parsing->files = malloc(sizeof(char *) * (parsing->nb_files + 1));
	if (!parsing->files) {
		write_error(NULL, NULL, errno);
		parsing->files = old;
		free_parsing(parsing);
		exit(EXIT_FAILURE);
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
		write_error(NULL, NULL, errno);
		parsing->strings = old;
		free_parsing(parsing);
		exit(EXIT_FAILURE);
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

	int only_files;

	if (argc < 2) {
		write(2, USAGE_MSG, ft_strlen(USAGE_MSG));
		exit(EXIT_FAILURE);
	}

	only_files = 0;
	init_parsing(parsing);
	for (int i = 2; i < argc; i++) {
		if (!only_files && argv[i][0] == '-') {
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
							goto next_arg;
						} else {
							write(2, NO_ARG_S_MSG, ft_strlen(NO_ARG_S_MSG));
							free_parsing(parsing);
							exit(EXIT_FAILURE);
						}
					default:
						break;
				}
			}
			next_arg:;
		} else {
			only_files = 1;
			add_file(parsing, argv[i]);
		}
	}
	return;
}