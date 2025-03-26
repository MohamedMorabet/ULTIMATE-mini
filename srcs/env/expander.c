/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:25:09 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/26 03:17:02 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *append_char(char *str, char c)
{
    char    mystr[2];
    char *new_str;

    mystr[0] = c;
    mystr[1] = 0;
    new_str = ft_strjoin(str, mystr);
    free(str);
    return (new_str);
}

static char *handle_var_expansion(char *args, int *i, t_envnode *env_list)
{
    char *result;
    int start;
    char *var_name;

    result = NULL;
    if (args[*i] == '?')
    {
        (*i)++;
        result = handle_lstatus_var();
    }
    else if (isalnum(args[*i]) || args[*i] == '_')
    {
        start = *i - 1;
        while (args[*i] && (isalnum(args[*i]) || args[*i] == '_'))
            (*i)++;
        var_name = strndup(args + start, *i - start);
        result = ft_getenv(var_name, env_list);
        free(var_name);
    }
    else
        result = ft_strdup("$");
    return (result);
}

static void	update_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

static char	*process_dollar(const char *args, int *i, char *result,
								t_envnode *env_list)
{
	char	*var_value;
	char	*new_result;

	(*i)++;
	var_value = handle_var_expansion((char *)args, i, env_list);
	if (var_value)
	{
	    new_result = ft_strjoin(result, var_value);
		free(result);
		free(var_value);
		return (new_result);
	}
	return (result);
}

char	*expand_env_vars(char *args, t_envnode *env_list)
{
	char	*result;
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	result = malloc(1);
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	if (!args || !result)
		return (free(result), NULL);
	result[0] = '\0';
	while (args[i])
	{
		update_quotes(args[i], &in_single_quote, &in_double_quote);
		if (args[i] == '$' && !in_single_quote)
			result = process_dollar(args, &i, result, env_list);
		else
			result = append_char(result, args[i++]);
	}
    if (result[0] == '\0')
        return (NULL);
	return (result);
}

char *process_expansion(char *arg, t_envnode *env_list)
{
    if (!arg)
        return (NULL);

    char *result = malloc(1);
    int i = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;

    if (!result)
        return (NULL);
    result[0] = '\0';

    while (arg[i])
    {
        update_quotes(arg[i], &in_single_quote, &in_double_quote);
        if (arg[i] == '$' && !in_single_quote) // Expand $VAR only outside single quotes
            result = process_dollar(arg, &i, result, env_list);
        else
            result = append_char(result, arg[i++]);
    }
    if (result[0] == '\0')
        return (NULL);
    return result;
}

char **ft_split_quotes(char *str)
{
    // This function correctly handles splitting, preserving quotes
    char **result = malloc(sizeof(char *) * 1024);
    if (!result)
        return NULL;

    int i = 0, j = 0, in_quotes = 0;
    char *word = malloc(1024);

    for (int k = 0; str[k]; k++)
    {
        if (str[k] == '"' || str[k] == '\'')
            in_quotes = !in_quotes;
        else if (str[k] == ' ' && !in_quotes) // Only split if outside quotes
        {
            word[j] = '\0';
            result[i++] = strdup(word);
            j = 0;
        }
        else
            word[j++] = str[k];
    }

    if (j > 0)
    {
        word[j] = '\0';
        result[i++] = strdup(word);
    }

    result[i] = NULL;
    free(word);
    return result;
}

char    **expand_env_vars2(char **args, t_envnode *env_list)
{
    int i = 0;
    char **new_args;
    
    if (!args)
        return (NULL);
    new_args = malloc(sizeof(char *) * 1024); // Temporary new args array
    if (!new_args)
        return (NULL);

    int new_index = 0;
    while (args[i])
    {
        char *expanded = process_expansion(args[i], env_list);  // Expand variable
        char **split_words = ft_split(expanded, ' '); // Split expansion
        int j = 0;
        while (split_words && split_words[j])
        {
            // Check if a word still contains spaces (meaning it was inside quotes)
            if (strchr(split_words[j], ' '))
            {
                char **resplit = ft_split_quotes(split_words[j]); // Custom function that handles quotes
                int k = 0;
                while (resplit[k])
                    new_args[new_index++] = strdup(resplit[k++]); // Add properly split words
                
                free_split(resplit);
            }
            else
            {
                new_args[new_index++] = strdup(split_words[j]); // Just copy normally split word
            }
            j++;
        }

        free(expanded);
        free_split(split_words);
        i++;
    }
    new_args[new_index] = NULL;
    
    free_split(args); // Free old args array
    return (new_args);  // Replace with new expanded array
}
