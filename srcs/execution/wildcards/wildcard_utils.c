/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:15:07 by mel-mora          #+#    #+#             */
/*   Updated: 2025/04/10 22:28:52 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

/*
 * Check a directory entry and add it to the match array if it fits.
 * If the pattern is exactly "*" then we include hidden files too.
 * We always skip "." and "..".
 */
void	check_and_add(const char *pattern, struct dirent *entry,
			t_matches_ctx *ctx)
{
	char	**temp;

	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		return ;
	if (pattern[0] != '.' && entry->d_name[0] == '.')
		return ;
	if (!match_pattern(pattern, entry->d_name))
		return ;
	if (ctx->cnt >= ctx->cap - 1)
	{
		ctx->cap *= 2;
		temp = realloc(ctx->matches, sizeof(char *) * ctx->cap);
		if (!temp)
			exit(EXIT_FAILURE);
		ctx->matches = temp;
	}
	ctx->matches[ctx->cnt] = strdup(entry->d_name);
	if (!ctx->matches[ctx->cnt])
	{
		print_error("malloc", NULL);
		exit(EXIT_FAILURE);
	}
	ctx->cnt++;
}

/*
 * Compute the total space required to join the matched strings with a
   separating space.
 */
size_t	compute_total(char **matches)
{
	size_t	total;
	size_t	i;

	total = 0;
	i = 0;
	while (matches && matches[i])
	{
		total += strlen(matches[i]) + 1;
		i++;
	}
	return (total);
}

/*
 * Build a single result string from the matches array.
 * The matches are concatenated with a space between each.
 */
char	*build_result(char **matches, size_t total)
{
	char	*res;
	size_t	i;

	res = malloc(total + 1);
	if (!res)
	{
		perror("malloc");
		return (NULL);
	}
	res[0] = '\0';
	i = 0;
	while (matches && matches[i])
	{
		strcat(res, matches[i]);
		if (matches[i + 1])
			strcat(res, " ");
		free(matches[i]);
		i++;
	}
	return (res);
}

// using while loop
static void	sort_matches(char **matches, size_t cnt)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (i < cnt - 1)
	{
		j = i + 1;
		while (j < cnt)
		{
			if (strcmp(matches[i], matches[j]) > 0)
			{
				temp = matches[i];
				matches[i] = matches[j];
				matches[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
 * Scan the current directory and collect all entries that match the given
   pattern.
 */
char	**expand_wildcard(const char *pattern)
{
	t_matches_ctx	ctx;
	struct dirent	*entry;

	ctx.cnt = 0;
	ctx.cap = 10;
	ctx.matches = malloc(sizeof(char *) * ctx.cap);
	if (!ctx.matches)
		return (print_error("malloc", NULL), NULL);
	ctx.dir = opendir(".");
	if (!ctx.dir)
	{
		print_error("opendir", NULL);
		return (free(ctx.matches), NULL);
	}
	entry = readdir(ctx.dir);
	while (entry != NULL)
	{
		check_and_add(pattern, entry, &ctx);
		entry = readdir(ctx.dir);
	}
	closedir(ctx.dir);
	if (ctx.cnt > 0)
		sort_matches(ctx.matches, ctx.cnt);
	ctx.matches[ctx.cnt] = NULL;
	return (ctx.matches);
}
