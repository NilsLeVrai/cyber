#include "../includes/sha256.h"
#include "../includes/utils.h"

static const uint32_t K[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
								0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
								0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
								0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
								0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
								0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
								0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
								0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

static void init_hash_values(t_init_values *init_hash) {

	init_hash->h0 = 0x6a09e667;
	init_hash->h1 = 0xbb67ae85;
	init_hash->h2 = 0x3c6ef372;
	init_hash->h3 = 0xa54ff53a;
	init_hash->h4 = 0x510e527f;
	init_hash->h5 = 0x9b05688c;
	init_hash->h6 = 0x1f83d9ab;
	init_hash->h7 = 0x5be0cd19;
	return ;
}

static char *compute_SHA256_hash(char *msg,  size_t len) {

	char			*padded;
	char			*hash;
	t_init_values	init_values;
	size_t			padded_len;

	init_hash_values(&init_values);
	padded = padded_buffer_sha256(msg, len, &padded_len);
	if (!padded)
		return NULL;
	for (char *chunk = padded; chunk < padded + padded_len; chunk += 64)
		sha256_operations(&init_values, (uint32_t *)chunk);
	free(padded);
	hash = malloc(sizeof(char) * 65);
	if (!hash)
		return NULL;
	to_hex_be(init_values.h0, hash);
	to_hex_be(init_values.h1, hash + 8);
	to_hex_be(init_values.h2, hash + 16);
	to_hex_be(init_values.h3, hash + 24);
	to_hex_be(init_values.h4, hash + 32);
	to_hex_be(init_values.h5, hash + 40);
	to_hex_be(init_values.h6, hash + 48);
	to_hex_be(init_values.h7, hash + 56);
	hash[64] = '\0';
	return hash;
}

char *padded_buffer_sha256(char *message, size_t len, size_t *padded_len) {

	char	*sha256_buffer;
	size_t	tmp;

	*padded_len = ((len + 1 + 8 + 63) / 64) * 64;
	sha256_buffer = malloc(sizeof(char) * *padded_len);
	if (!sha256_buffer)
		return NULL;
	for (size_t i = 0; i < len; i++) {
		sha256_buffer[i] = message[i];
	}
	tmp = len;
	sha256_buffer[len] = 0x80;
	len++;
	while (len < *padded_len - 8) {
		sha256_buffer[len] = 0x0;
		len++;
	}
	for (int i = 7; i >= 0; i--)
		sha256_buffer[*padded_len - 8 + i] = ((tmp * 8) >> ((7 - i) * 8)) & 0xFF;
	return sha256_buffer;
}

static uint32_t rightrotate(uint32_t x, uint32_t n) {
	return (x >> n) | (x << (32 - n));
}

void sha256_operations(t_init_values *init_values, uint32_t *M) {

	unsigned char	*bytes = (unsigned char *)M;
	uint32_t		w[64];
	uint32_t		a = init_values->h0;
	uint32_t		b = init_values->h1;
	uint32_t		c = init_values->h2;
	uint32_t		d = init_values->h3;
	uint32_t		e = init_values->h4;
	uint32_t		f = init_values->h5;
	uint32_t		g = init_values->h6;
	uint32_t		h = init_values->h7;

	for (int i = 0; i < 16; i++)
		w[i] = ((uint32_t)bytes[i * 4] << 24) | ((uint32_t)bytes[i * 4 + 1] << 16) | ((uint32_t)bytes[i * 4 + 2] << 8) | (uint32_t)bytes[i * 4 + 3];

	for (int i = 16; i < 64; i++) {
		uint32_t	s0 = rightrotate(w[i - 15], 7) ^ rightrotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
		uint32_t	s1 = rightrotate(w[i - 2], 17) ^ rightrotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

	for (int i = 0; i < 64; i++) {
		uint32_t	S1 = rightrotate(e, 6) ^ rightrotate(e, 11) ^ rightrotate(e, 25);
		uint32_t	ch = (e & f) ^ (~e & g);
		uint32_t	tmp1 = h + S1 + ch + K[i] + w[i];
		uint32_t	S0 = rightrotate(a, 2) ^ rightrotate(a, 13) ^ rightrotate(a, 22);
		uint32_t	maj = (a & b) ^ (a & c) ^ (b & c);
		uint32_t	tmp2 = S0 + maj;

		h = g;
		g = f;
		f = e;
		e = d + tmp1;
		d = c;
		c = b;
		b = a;
		a = tmp1 + tmp2;
	}

	init_values->h0 += a;
	init_values->h1 += b;
	init_values->h2 += c;
	init_values->h3 += d;
	init_values->h4 += e;
	init_values->h5 += f;
	init_values->h6 += g;
	init_values->h7 += h;
}


int	ft_sha256(t_hash_parsing *parsing)
{
	return ft_do_hash(parsing, compute_SHA256_hash, "SHA256");
}