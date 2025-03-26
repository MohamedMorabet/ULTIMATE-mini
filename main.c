#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "srcs/libft/libft.h"

void append_char(char **str, char c)
{
    char    mystr[2];
    char *new_str;

    mystr[0] = c;
    mystr[1] = 0;
    char *tmp = *str;
    *str = ft_strjoin(*str, mystr);
    if (tmp == NULL)
        free(tmp);
}

char *remove_first_layer_quotes(char *input)
{
    char quote;
    size_t len = strlen(input);
    char *result = ft_strdup("");
    if (len < 2) return strdup(input); // Nothing to remove

    int i = 0;

    if (input[i] == '\'' || input[i] == '"')
    {
        quote = input[i];
        i++;
        while (input[i] && input[i] != quote)
        {
            i++;
        }
        if (input[i + 1] == 0)
        {
            return input;
        }
        else
        {
            result = ft_substr(input, 1, i - 1);
        }
        i++;

    }
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            quote = input[i];
            i++;
            while (input[i] && input[i] != quote)
            {
                append_char(&result, input[i]);
                i++;
            }
            i++;
        }
        else
        {
            append_char(&result, input[i]);
            i++;
        }
    }
    return (result);
}

int main()
{
    
   while (1)
   {
        char name[100];
        scanf("%s", name);
        fflush(stdin);
        printf("=== > %s\n", remove_first_layer_quotes(name));
   }
    return 0;
}   