#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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

int ft_strlen(const char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}
/*
A = 65 DEC
A = 01000001 BIN
2*7 + 2*0
64 + 1
*/
void convert(char *s) {
    int len_message = ft_strlen(s);
    int i = 0;
    int j = 0;
    char *string = malloc(sizeof(char) * len_message * 8 + 2);
    if (!s)
        return ;
    printf("DEBUG: len_message %d\n", len_message);
    while (i < len_message) {
        unsigned char c = (unsigned char)s[i];
        printf("DEBUG: %c\n", c);
        for (int bit = 7; bit >= 0; --bit)
            string[j++] = ((c >> bit) & 1) ? '1' : '0';
        i++;
    }
    string[j++] = '1';
    string[j++] = '\0';
    printf("DEBUGGG: %s\n", string);
    putchar('\n');
    return ;
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        write(1, "Usage\n", 6);
        return 0;
    }
    // char *s = "\n";
    // printf("len: %d\n", ft_strlen(s));
    convert(argv[1]);
    return (0);
}