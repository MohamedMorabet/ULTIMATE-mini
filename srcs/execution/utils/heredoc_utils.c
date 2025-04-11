/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mest <oel-mest@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:37:24 by mel-mora          #+#    #+#             */
/*   Updated: 2025/04/11 16:59:54 by oel-mest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

//tmp[20] Enough to hold any int value 
static void	generate_filename(char *dest, size_t size, int count)
{
	size_t		i;
	const char	*prefix;
	char		temp[20];
	int			pos;

	i = -1;
	prefix = "/tmp/minihell_heredoc_";
	while (prefix[++i] && i < size - 1)
		dest[i] = prefix[i];
	pos = 0;
	if (count == 0)
		temp[pos++] = '0';
	else
	{
		while (count > 0 && pos < (int)(sizeof(temp) - 1))
		{
			temp[pos++] = '0' + (count % 10);
			count /= 10;
		}
	}
	while (pos > 0 && i < size - 1)
		dest[i++] = temp[--pos];
	dest[i] = '\0';
}

void	process_heredoc_entry(t_output *current, t_envnode **envp)
{
	static int	heredoc_count;
	char		filename[64];
	int			fd;
	char		*clean_delimiter;
	int			expand_vars;

	generate_filename(filename, sizeof(filename), heredoc_count);
	heredoc_count++;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error("heredoc temp file", NULL);
		exit(1);
	}
	expand_vars = is_quoted_delimiter(current->file);
	clean_delimiter = remove_quotes(current->file);
	clean_delimiter = remove_first_layer_quotes(clean_delimiter);
	process_heredoc_input(fd, clean_delimiter, expand_vars, envp);
	close(fd);
	free(current->file);
	current->file = ft_strdup(filename);
	free(clean_delimiter);
}
