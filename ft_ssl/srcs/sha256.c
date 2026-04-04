#include "../includes/sha256.h"

char	*ft_sha256(t_hash_parsing *parsing) {
	(void)parsing;
	write(1, "sha256\n", 7);
	return NULL;
}