#include "../includes/sha256.h"
#include "../includes/utils.h"

static char *compute_SHA256_hash(char *msg,  size_t len) {
	(void) msg;
	(void)len;
	return "oui";
} 

void	ft_sha256(t_hash_parsing *parsing)
{
	ft_do_hash(parsing, compute_SHA256_hash, "SHA256", "sha256");
}
