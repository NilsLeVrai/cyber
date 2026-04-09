#pragma once

#include "parsing.h"
#include "utils.h"
#include <unistd.h>
#include <stdint.h>

typedef struct s_four_word_buffer {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} t_words;

char	*compute_hash(char *msg,  size_t len);
char	*padded_buffer(char *message, size_t len, size_t *padded_len);
char	*read_stdin(size_t *padded_len);
void	ft_md5(t_hash_parsing *parsing);
void	operations(t_words *words, uint32_t *M);
