#include "../includes/utils.h"

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