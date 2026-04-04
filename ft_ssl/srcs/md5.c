#include "../includes/md5.h"
#include <stdio.h>

static int ft_strlen(char *s) {
	size_t i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

static void init_words(t_words *words) {

	words->word_a = 0x67452301;
	words->word_b = 0xefcdab89;
	words->word_c = 0x98badcfe;
	words->word_d = 0x10325476;
	return ;
}

static unsigned char *padded_buffer(char *message, size_t len, size_t *padded_len) {

	unsigned char	*md5_buffer;
	size_t			tmp;

	*padded_len = ((len + 1 + 8 + 63) / 64) * 64;
	md5_buffer = malloc(sizeof(char) * *padded_len);
	if (!md5_buffer)
		return NULL;
	for (size_t i = 0; i < len; i++) {
		md5_buffer[i] = message[i];
	}
	tmp = len;
	md5_buffer[len] = 0x80;
	len++;
	while (len < *padded_len - 8) {
		md5_buffer[len] = 0x0;
		len++;
	}
	for (int i = 0; i < 8; i++)
        md5_buffer[*padded_len - 8 + i] = ((tmp * 8) >> (i * 8)) & 0xFF;
	return md5_buffer;
}

char	*ft_md5(t_hash_parsing *parsing) {

	unsigned char	*padded;
	t_words			words;
	size_t			padded_len;

	init_words(&words);
	padded = padded_buffer(parsing->strings[0], ft_strlen(parsing->strings[0]), &padded_len);
	(void) padded;
	write(1, "md5\n", 4);
	return NULL;
}
