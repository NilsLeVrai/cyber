#include "includes/ft_ssl.h"
#include <stdio.h>
/*
MD5("The quick brown fox jumps over the lazy dog") =
9e107d9d372bb6826bd81d3542a419d6

open
close
read
write
malloc
free
*/

int main(int argc, char **argv)
{
	t_hash_parsing	parsing;

	check_parsing(argc, argv, &parsing);
	if (argc > 2)
		dispatcher(argv[1], &parsing);
    return (0);
}