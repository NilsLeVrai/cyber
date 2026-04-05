#pragma once

#include "parsing.h"
#include <unistd.h>
#include <stdint.h>

typedef struct s_four_word_buffer {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} t_words;

char	*ft_md5(t_hash_parsing *parsing);