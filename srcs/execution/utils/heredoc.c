/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:35:41 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/26 02:41:43 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

void	prepare_heredocs(t_ast *node, t_envnode **envp)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->cmd->heredoc2)
		collect_heredoc(node->cmd, envp);
	prepare_heredocs(node->left, envp);
	prepare_heredocs(node->right, envp);
}

void	process_heredoc_input(int fd, char *clean_delimiter,
			int expand_vars, t_envnode **envp)
{
	char	buffer[1024];
	char	*expanded_buffer;
	size_t	delim_len;

	delim_len = strlen(clean_delimiter);
	while (1)
	{
		printf("> ");
		if (!fgets(buffer, sizeof(buffer), stdin))
			break ;
		if (strncmp(buffer, clean_delimiter, delim_len) == 0
			&& buffer[delim_len] == '\n')
			break ;
		if (expand_vars)
			expanded_buffer = expand_env_vars(buffer, *envp);
		else
			expanded_buffer = strdup(buffer);
		write(fd, expanded_buffer, strlen(expanded_buffer));
		free(expanded_buffer);
	}
}

void	process_heredoc_entry(t_output *current, t_envnode **envp)
{
	static int	heredoc_count;
	char		filename[64];
	int			fd;
	char		*clean_delimiter;
	int			expand_vars;

	/* ensure heredoc_count is used as static */
	heredoc_count = heredoc_count;
	snprintf(filename, sizeof(filename),
		"/tmp/minihell_heredoc_%d", heredoc_count);
	heredoc_count = heredoc_count + 1;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error("heredoc temp file", NULL);
		exit(1);
	}
	clean_delimiter = remove_quotes(current->file);
	expand_vars = !is_quoted_delimiter(current->file);
	process_heredoc_input(fd, clean_delimiter, expand_vars, envp);
	close(fd);
	free(current->file);
	current->file = strdup(filename);
	free(clean_delimiter);
}

void	collect_heredoc(t_cmd *cmd, t_envnode **envp)
{
	t_output	*current;

	current = cmd->heredoc2;
	while (current)
	{
		process_heredoc_entry(current, envp);
		current = current->next;
	}
}

void	handle_heredoc_if_needed(t_cmd *cmd)
{
	t_output	*current;
	int			fd;

	current = cmd->heredoc2;
	while (current)
	{
		if (access(current->file, F_OK) == 0)
		{
			fd = open(current->file, O_RDONLY);
			if (fd < 0)
			{
				print_error("open", current->file, NULL);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		current = current->next;
	}
}
