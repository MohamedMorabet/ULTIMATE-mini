/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:27:12 by mel-mora          #+#    #+#             */
/*   Updated: 2025/04/10 22:28:56 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

/* Helper: Check if the string is composed entirely of '*' */
int	is_all_stars(const char *s)
{
	while (*s)
	{
		if (*s != '*')
			return (0);
		s++;
	}
	return (1);
}

/*
 * Expand a token: if it contains a '*' then perform wildcard expansion,
 * otherwise simply duplicate the token.
 */
char	*expand_token(const char *token)
{
	char	**matches;
	size_t	total;
	char	*res;

	if (!strchr(token, '*'))
		return (strdup(token));
	matches = expand_wildcard(token);
	if (!matches || !matches[0])
	{
		if (matches)
			free(matches);
		return (strdup(token));
	}
	total = compute_total(matches);
	res = build_result(matches, total);
	free(matches);
	return (res);
}

/* 
 * Recursively match a pattern against a string.
 * The pattern supports '*' as a wildcard for any number of characters.
 */
int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		if (is_all_stars(pattern))
			return (1);
		while (*(pattern + 1) == '*')
			pattern++;
		while (*str)
		{
			if (match_pattern(pattern + 1, str))
				return (1);
			str++;
		}
		return (match_pattern(pattern + 1, str));
	}
	else
	{
		if (*pattern == *str)
			return (match_pattern(pattern + 1, str + 1));
		return (0);
	}
}
