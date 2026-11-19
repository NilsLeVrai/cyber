#include "includes/ft_ssl.h"

int main(int argc, char **argv)
{
	t_hash_parsing	parsing;

	check_parsing(argc, argv, &parsing);
	return (dispatcher(argv[1], &parsing));
}