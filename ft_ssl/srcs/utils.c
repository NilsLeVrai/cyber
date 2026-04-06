#include "../includes/utils.h"

void write_error(char *argv, int *err) {
	char *msg = argv;

	write(2, "ft_ssl: ", 8);
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, strerror(*err), ft_strlen(strerror(*err)));
	write(2, "\n", 1);
}

char *to_hex(uint32_t value, char *output) {

	uint8_t	byte;
	for (int i = 0; i < 4; i++) {
		byte = (value >> (i * 8)) & 0xFF;
		output[i * 2]     = "0123456789abcdef"[(byte >> 4) & 0xF];                          
		output[i * 2 + 1] = "0123456789abcdef"[byte & 0xF];
	}
	return output;
}

int ft_strlen(char *s) {
	size_t i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

int ft_strcmp(char *s1, char *s2) {
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

void print_hash(char *hash, char *source, t_hash_parsing *parsing, char *cmd, t_source type) {
	
	if (parsing->flag_q) {
		write(1, hash, ft_strlen(hash));
		write(1, "\n", 1);
	} else if (parsing->flag_r && type == STRING) {
		write(1, hash, ft_strlen(hash));
		write(1, " \"", 2);
		write(1, source, ft_strlen(source));
		write(1, "\"", 1);
		write(1, "\n", 1);
	} else if (parsing->flag_r && type == FILE_SRC) {
		write(1, hash, ft_strlen(hash));
		write(1, " ", 1);
		write(1, source, ft_strlen(source));
		write(1, "\n", 1);
	} else if (parsing->flag_p) {
		write(1, "(\"", 2);
		write(1, source, ft_strlen(source));
		write(1, "\")= ", 4);
		write(1, hash, ft_strlen(hash));
		write(1, "\n", 1);
	} else if (type == STDIN && !parsing->flag_p) {
		write(1, "(stdin)= ", 9);
		write(1, hash, ft_strlen(hash));
		write(1, "\n", 1);
	} else if (type == STRING) {
		write(1, cmd, ft_strlen(cmd));
		write(1, " (\"", 3);
		write(1, source, ft_strlen(source));
		write(1, "\") = ", 5);
		write(1, hash, ft_strlen(hash));
		write(1, "\n", 1);
	} else if (type == FILE_SRC) {
		write(1, cmd, ft_strlen(cmd));
		write(1, " (", 2);
		write(1, source, ft_strlen(source));
		write(1, ") = ", 4);
		write(1, hash, ft_strlen(hash));
		write(1, "\n", 1);
	}
}