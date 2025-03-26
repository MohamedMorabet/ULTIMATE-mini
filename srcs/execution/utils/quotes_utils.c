/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:38:11 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/26 00:47:06 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

char	*remove_quotess(const char *str)
{
	int		i;
	int		j;
	int		len;
	char	*cleaned;

	if (!str)
		return (NULL);
	len = strlen(str);
	cleaned = malloc(len + 1);
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '"')
			cleaned[j++] = str[i];
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}

char	*remove_quotes(const char *str)
{
	size_t	len;
	char	*clean;

	len = strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		clean = strndup(str + 1, len - 2);
		return (clean);
	}
	return (strdup(str));
}

char	*remove_first_layer_quotes(char *input)
{
	size_t	len;
	char	*result;
	int		i;

	len = strlen(input);
	if (len < 2)
	{
		result = strdup(input);
		free(input);
		return (result);
	}
	result = process_initial_part(input, &i);
	if (result == input)
		return (input);
	process_remaining_chars(input, &i, &result);
	free(input);
	return (result);
}

char	*get_first_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (ft_substr(str, 0, i));
}
