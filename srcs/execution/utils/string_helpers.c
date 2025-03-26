/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:39:42 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/25 23:52:25 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

char	*process_initial_part(char *input, int *i)
{
	char	quote;
	char	*result;

	*i = 0;
	result = ft_strdup("");
	if (input[*i] == '\'' || input[*i] == '"')
	{
		quote = input[*i];
		*i = *i + 1;
		while (input[*i] && input[*i] != quote)
		{
			*i = *i + 1;
		}
		if (input[*i + 1] == '\0')
		{
			free(result);
			return (input);
		}
		else
		{
			free(result);
			result = ft_substr(input, 1, *i - 1);
		}
		*i = *i + 1;
	}
	return (result);
}

void	process_remaining_chars(char *input, int *i, char **result)
{
	char	quote;

	while (input[*i])
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			*i = *i + 1;
			while (input[*i] && input[*i] != quote)
			{
				append_char(result, input[*i]);
				*i = *i + 1;
			}
			*i = *i + 1;
		}
		else
		{
			append_char(result, input[*i]);
			*i = *i + 1;
		}
	}
}

void	append_char(char **str, char c)
{
	char	mystr[2];
	char	*new_str;
	char	*tmp;

	mystr[0] = c;
	mystr[1] = 0;
	tmp = *str;
	*str = ft_strjoin(*str, mystr);
	if (tmp)
		free(tmp);
}
