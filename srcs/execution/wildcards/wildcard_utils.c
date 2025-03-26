/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:15:07 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/25 21:29:18 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

int	match_pattern(const char *p, const char *s)
{
	if (*p == '\0')
		return (!*s);
	if (*p == '*')
	{
		while (*(p + 1) == '*')
			p++;
		if (*(p + 1) == '\0')
			return (1);
		while (*s)
		{
			if (match_pattern(p + 1, s))
				return (1);
			s++;
		}
		return (match_pattern(p + 1, s));
	}
	if (*p == *s)
		return (match_pattern(p + 1, s + 1));
	return (0);
}

void	check_and_add(const char *pattern, struct dirent *entry,
			t_matches_ctx *ctx)
{
	if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
		return ;
	if (!match_pattern(pattern, entry->d_name))
		return ;
	if (ctx->cnt >= ctx->cap - 1)
	{
		ctx->cap = ctx->cap * 2;
		ctx->matches = realloc(ctx->matches, sizeof(char *) * (ctx->cap));
	}
	ctx->matches[ctx->cnt] = strdup(entry->d_name);
	ctx->cnt++;
}

size_t	compute_total(char **matches)
{
	size_t	i;
	size_t	total;

	i = 0;
	total = 0;
	while (matches[i])
	{
		total += strlen(matches[i]) + 1;
		i++;
	}
	return (total);
}

char	*build_result(char **matches, size_t total)
{
	char	*res;
	size_t	i;

	res = malloc(total);
	if (res == NULL)
		return (NULL);
	res[0] = '\0';
	i = 0;
	while (matches[i])
	{
		strcat(res, matches[i]);
		if (matches[i + 1] != NULL)
			strcat(res, " ");
		free(matches[i]);
		i++;
	}
	return (res);
}

char	**expand_wildcard(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_matches_ctx	ctx;

	ctx.cnt = 0;
	ctx.cap = 10;
	ctx.matches = malloc(sizeof(char *) * ctx.cap);
	if (ctx.matches == NULL)
		return (NULL);
	dir = opendir(".");
	if (dir == NULL)
	{
		free(ctx.matches);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		check_and_add(pattern, entry, &ctx);
		entry = readdir(dir);
	}
	closedir(dir);
	ctx.matches[ctx.cnt] = NULL;
	return (ctx.matches);
}
