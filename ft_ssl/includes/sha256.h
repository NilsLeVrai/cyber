#pragma once

#include "parsing.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct s_initial_hash_value {
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
    uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;
} t_init_values;

void	ft_sha256(t_hash_parsing *parsing);
