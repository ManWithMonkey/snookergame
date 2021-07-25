#define RED "\e[0;31m"
#define reset "\e[0m"

#include <cstdio>

int main (void)
{
	char string[] =
	"  sometext  " RED  "/---\\" reset "  sometext   \n"
	"  sometext  " RED  "| 8 |"  reset "  sometext   \n"
	"  sometext  " RED "\\---/"  reset "  sometext   \n"
	;
	printf("%s\n", string);
}