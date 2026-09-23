#include <stdio.h>

/*
My first comment
*/

void ft_return() {
	return;
}

int main()
{
	//    My   second comment
	char *s = "#include <stdio.h>%c%c/*%cMy first comment%c*/%c%cvoid ft_return() {%c%creturn;%c}%c%cint main()%c{%c%c//    My   second comment%c%cchar *s = %c%s%c;%c%cprintf(s, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 9, 10, 9, 34, s, 34, 10, 9, 10, 9, 10, 10);%c%cft_return();%c}";
	printf(s, 10, 10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 9, 10, 9, 34, s, 34, 10, 9, 10, 9, 10, 10);
	ft_return();
}