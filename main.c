#include "libasm.h"

#include <stdio.h>
#include <string.h>

static int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

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
        char ft_dst[100] = "xxxxxxxxxxxxxxxx";
        char libc_dst[100] = "xxxxxxxxxxxxxxxx";
        char *ft_ret;
        char *libc_ret;

        ft_ret = ft_strcpy(ft_dst, tests[i]);
        libc_ret = strcpy(libc_dst, tests[i]);

        printf("test: \"%s\"\n", tests[i]);
        printf("ft_strcpy = \"%s\"\n", ft_dst);
        printf("strcpy    = \"%s\"\n", libc_dst);
        printf("return    = %s\n",
            ft_ret == ft_dst && libc_ret == libc_dst ? "OK" : "KO");
        printf("result    = %s\n\n",
            strcmp(ft_dst, libc_dst) == 0
                && ft_ret == ft_dst
                && libc_ret == libc_dst
                ? "OK"
                : "KO");
    }

    printf("----- strcmp -----\n");
    {
        const char *strcmp_tests[][2] = {
            {"", ""},
            {"a", ""},
            {"", "a"},
            {"abc", "abc"},
            {"abc", "abd"},
            {"abd", "abc"},
            {"abc", "abcd"},
            {"abcd", "abc"},
            {"bonjour", "bonsoir"},
        };

        for (int i = 0; i < 9; i++)
        {
            int ft_ret = ft_strcmp(strcmp_tests[i][0], strcmp_tests[i][1]);
            int libc_ret = strcmp(strcmp_tests[i][0], strcmp_tests[i][1]);

            printf("\"%s\" / \"%s\"\n", strcmp_tests[i][0], strcmp_tests[i][1]);
            printf("ft_strcmp = %d\n", ft_ret);
            printf("strcmp    = %d\n", libc_ret);
            printf("result    = %s\n\n",
                sign(ft_ret) == sign(libc_ret) ? "OK" : "KO");
        }
    }

    return 0;
}
