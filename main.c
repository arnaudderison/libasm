#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t ft_strlen(const char *s);

int main(void)
{
    const char *tests[] = {
        "",
        "a",
        "hello",
        "bonjour les amis",
        "42"
    };

    for (int i = 0; i < 5; i++)
    {
        printf("test: \"%s\"\n", tests[i]);
        printf("ft_strlen = %zu\n", ft_strlen(tests[i]));
        printf("strlen    = %zu\n\n", strlen(tests[i]));
    }

    return 0;
}