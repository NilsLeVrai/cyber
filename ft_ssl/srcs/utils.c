#include "../includes/utils.h"

void write_error(char *subcmd, char *argv, int err) {
	write(2, "ft_ssl: ", 8);
	write(2, subcmd, ft_strlen(subcmd));
	write(2, ": ", 2);
	write(2, argv, ft_strlen(argv));
	write(2, ": ", 2);
	write(2, strerror(err), ft_strlen(strerror(err)));
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

char *to_hex_be(uint32_t value, char *output) {
	uint8_t	byte;
	for (int i = 0; i < 4; i++) {
		byte = (value >> ((3 - i) * 8)) & 0xFF;
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

char *read_file(char *path, size_t *len) {

	char	buf[1024];
	char	*file_buffer;
	char	*tmp;
	int		n;
	int		fd;


	file_buffer = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return NULL;
	while((n = read(fd, buf, 1024)) > 0) {
		tmp = malloc(sizeof(char) * (n + *len));
		if (!tmp)
			return NULL;
		for (size_t i = 0; i < *len; i++)
			tmp[i] = file_buffer[i];
		for (int j = 0; j < n; j++)
			tmp[j + *len] = buf[j];
		free(file_buffer);
		file_buffer = tmp;
		*len += n;
	}
	close(fd);
	if (!file_buffer) {
		file_buffer = malloc(1);
		if (!file_buffer)
			return NULL;
	}
	return file_buffer;
}

char *read_stdin(size_t *len) {

	char	buf[1024];
	char	*stdin_buffer;
	char	*tmp;
	int		n;

	stdin_buffer = NULL;
	while((n = read(0, buf, 1024)) > 0) {
		tmp = malloc(sizeof(char) * (n + *len + 1));
		if (!tmp)
			return NULL;
		for (size_t i = 0; i < *len; i++)
			tmp[i] = stdin_buffer[i];
		for (int j = 0; j < n; j++)
			tmp[j + *len] = buf[j];
		free(stdin_buffer);
		stdin_buffer = tmp;
		*len += n;
	}
	if (stdin_buffer == NULL) {
		stdin_buffer = malloc(1);
		if (!stdin_buffer)
			return NULL;
	}
	stdin_buffer[*len] = '\0';
	return stdin_buffer;
}

void	ft_do_hash(t_hash_parsing *parsing, char*(*compute)(char *, size_t), char *cmd, char *err_cmd) {
	size_t	len;
	char	*hash;
	char	*stdin_buffer;
	char	*file_buffer;

	hash = NULL;
	len = 0;
	if (parsing->flag_p) {
		stdin_buffer = read_stdin(&len);
		hash = compute(stdin_buffer, len);
		print_hash(hash, stdin_buffer, parsing, cmd, STDIN);
		free(stdin_buffer);
		free(hash);
		hash = NULL;
	}
	for (int i = 0; i < parsing->nb_strings; i++) {
		hash = compute(parsing->strings[i], ft_strlen(parsing->strings[i]));
		print_hash(hash, parsing->strings[i], parsing, cmd, STRING);
		free(hash);
		hash = NULL;
	}
	for (int i = 0; i < parsing->nb_files; i++) {
		len = 0;
		file_buffer = read_file(parsing->files[i], &len);
		if (!file_buffer) {
			write_error(err_cmd, parsing->files[i], errno);
			continue;
		}
		hash = compute(file_buffer, len);
		print_hash(hash, parsing->files[i], parsing, cmd, FILE_SRC);
		free(file_buffer);
		free(hash);
		hash = NULL;
	}
	len = 0;
	if (!parsing->flag_p && !parsing->nb_strings && !parsing->nb_files) {
		stdin_buffer = read_stdin(&len);
		hash = compute(stdin_buffer, len);
		print_hash(hash, NULL, parsing, cmd, STDIN);
		free(stdin_buffer);
	}
	if (hash)
		free(hash);
	return ;
}

void print_hash(char *hash, char *source, t_hash_parsing *parsing, char *cmd, t_source type) {
	
	if (parsing->flag_p && type == STDIN) {
		int src_len = ft_strlen(source);
		if (src_len > 0 && source[src_len - 1] == '\n')
			src_len--;
		if (parsing->flag_q) {
			write(1, source, src_len);
			write(1, "\n", 1);
			write(1, hash, ft_strlen(hash));
			write(1, "\n", 1);
		} else {
			write(1, "(\"", 2);
			write(1, source, src_len);
			write(1, "\")= ", 4);
			write(1, hash, ft_strlen(hash));
			write(1, "\n", 1);
		}
	} else if (parsing->flag_q) {
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