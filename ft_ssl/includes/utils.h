#pragma once

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "parsing.h"

typedef enum e_source {                             
	STDIN,
	STRING,
	FILE_SRC
} t_source; 

void write_error(char *argv, int *err);
char *to_hex(uint32_t value, char *output);
int ft_strlen(char *s);
int ft_strcmp(char *s1, char *s2);
void print_hash(char *hash, char *source, t_hash_parsing *parsing, char *cmd, t_source type);