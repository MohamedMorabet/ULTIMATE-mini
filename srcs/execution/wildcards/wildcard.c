/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:18:40 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/26 03:04:16 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

char	*expand_token(const char *token)
{
	char	**matches;
	char	*res;
	size_t	total;

	if (strchr(token, '*') == NULL)
		return (strdup(token));
	matches = expand_wildcard(token);
	if (matches == NULL || matches[0] == NULL)
	{
		if (matches != NULL)
			free(matches);
		return (strdup(token));
	}
	total = compute_total(matches);
	res = build_result(matches, total);
	free(matches);
	return (res);
}

char	*get_next_expanded_token(const char **line_ptr)
{
	const char	*p;
	const char	*start;
	char		*token;
	char		*exp;

	p = *line_ptr;
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == '\0')
		return (NULL);
	start = p;
	while (*p && *p != ' ' && *p != '\t')
		p++;
	token = strndup(start, p - start);
	exp = expand_token(token);
	free(token);
	*line_ptr = p;
	return (exp);
}

size_t	w_append_token(char **res_ptr, size_t pos,
			size_t *cap, const char *token)
{
	char	*res;
	size_t	token_len;

	res = *res_ptr;
	if (pos > 0)
	{
		if (pos + 1 >= *cap)
		{
			*cap = pos + 1 + 1024;
			res = realloc(res, *cap);
		}
		res[pos] = ' ';
		pos++;
		res[pos] = '\0';
	}
	token_len = strlen(token);
	if (pos + token_len + 1 >= *cap)
	{
		*cap = pos + token_len + 1024;
		res = realloc(res, *cap);
	}
	strcpy(res + pos, token);
	pos = pos + token_len;
	*res_ptr = res;
	return (pos);
}

static size_t	process_tokens(const char *p, char **res, size_t *cap)
{
	size_t	pos;
	char	*token;

	pos = 0;
	while (*p)
	{
		while (*p == ' ' || *p == '\t')
			p++;
		if (*p == '\0')
			break ;
		token = get_next_expanded_token(&p);
		if (!token)
			break ;
		pos = w_append_token(res, pos, cap, token);
		free(token);
	}
	return (pos);
}

char	*expand_line(char *line)
{
	char	*res;
	size_t	cap;
	size_t	pos;

	if (!line)
		return (NULL);
	cap = 1024;
	res = malloc(cap);
	if (!res)
		return (NULL);
	res[0] = '\0';
	pos = process_tokens(line, &res, &cap);
	if (pos == 0)
	{
		free(res);
		return (NULL);
	}
	free(line);
	return (res);
}
