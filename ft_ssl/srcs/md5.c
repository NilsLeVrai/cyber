#include "../includes/md5.h"
#include <stdio.h>

static uint32_t S[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
				5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
				4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
				6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
				0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
				0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
				0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
				0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
				0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
				0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
				0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
				0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
				0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
				0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
				0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
				0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
				0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
				0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
				0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static void init_words(t_words *words) {

	words->a = 0x67452301;
	words->b = 0xefcdab89;
	words->c = 0x98badcfe;
	words->d = 0x10325476;
	return ;
}

char *padded_buffer(char *message, size_t len, size_t *padded_len) {

	char	*md5_buffer;
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

void operations(t_words *words, uint32_t *M) {

	uint32_t	h0 = words->a;
	uint32_t	h1 = words->b;
	uint32_t	h2 = words->c;
	uint32_t	h3 = words->d;

	for (int i = 0; i < 64; i++) {
		uint32_t	f;
		uint32_t	g;
		uint32_t	tmp;
		if (i <= 15) {
			tmp = (words->b & words->c) | (~words->b & words->d);
			g = i;
		} else if (i >= 16 && i <= 31) {
			tmp = (words->b & words->d) | (words->c & ~words->d);
			g = (5 * i + 1) % 16;
		} else if (i >= 32 && i <= 47) {
			tmp = words->b ^ words->c ^ words->d;
			g = (3 * i + 5) % 16;
			
		} else {
			tmp = words->c ^ (words->b | ~words->d);
			g = (7 * i) % 16;
		}
		f = tmp;
		tmp = words->d;
		words->d = words->c;
		words->c = words->b;
		words->b = words->b + (((words->a + f + K[i] + M[g]) << S[i]) | ((words->a + f + K[i] + M[g]) >> (32 - S[i]))); 
		words->a = tmp;
	}
	words->a += h0;
	words->b += h1;
	words->c += h2;
	words->d += h3;
}

char	*ft_md5(t_hash_parsing *parsing) {

	char			*hash;
	char			*padded;
	t_words			words;
	size_t			padded_len;

	init_words(&words);
	padded = padded_buffer(parsing->strings[0], ft_strlen(parsing->strings[0]), &padded_len);
	for (char *chunk = padded; chunk < padded + padded_len; chunk += 64)
		operations(&words, (uint32_t *)chunk);
	hash = malloc(sizeof(char) * 33);
	if (!hash)
		return NULL;
	to_hex(words.a, hash);
	to_hex(words.b, hash + 8);
	to_hex(words.c, hash + 16);
	to_hex(words.d, hash + 24);
	hash[32] = '\0';
	write(1, hash, 32);
	return hash;
}
