#pragma once

#include "parsing.h"
#include <unistd.h>

typedef struct s_four_word_buffer {
	uint32_t word_a;
	uint32_t word_b;
	uint32_t word_c;
	uint32_t word_d;
} t_words;

char	*ft_md5(t_hash_parsing *parsing);