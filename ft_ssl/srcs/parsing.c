#include "../includes/ft_ssl.h"

static t_command commands[] = {
	{"md5", ft_md5},
	{"sha256", ft_sha256},
	{NULL, NULL}
};

static int ft_strcmp(char *s1, char *s2) {
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

char	*dispatcher(char *command, t_hash_parsing *parsing) {
	int i;

	i = 0;
	while (commands[i].name != NULL) {
		if (ft_strcmp(command, commands[i].name) == 0) {
			return commands[i].func(parsing);
		}
		i++;
	}
	return NULL;
}

void check_parsing(int argc, char **argv, t_hash_parsing *parsing) {
	(void)argc;
	(void)argv;
	(void)parsing;
	return;
}