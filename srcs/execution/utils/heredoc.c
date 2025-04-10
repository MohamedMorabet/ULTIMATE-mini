/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:35:41 by mel-mora          #+#    #+#             */
/*   Updated: 2025/04/10 22:38:01 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

void	prepare_heredocs(t_ast *node, t_envnode **envp)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->cmd->input2)
	{
		collect_heredoc(node->cmd, envp);
	}
	prepare_heredocs(node->left, envp);
	prepare_heredocs(node->right, envp);
}

void	process_heredoc_input(int fd, char *clean_delimiter,
		int expand_vars, t_envnode **envp)
{
	char	*line;
	char	*expanded_buffer;
	size_t	delim_len;

	delim_len = ft_strlen(clean_delimiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, clean_delimiter, delim_len) == 0
			&& line[delim_len] == '\n')
		{
			free(line);
			break ;
		}
		if (expand_vars)
			expanded_buffer = expand_env_vars(line, *envp);
		else
			expanded_buffer = ft_strdup(line);
		write(fd, expanded_buffer, ft_strlen(expanded_buffer));
		free(expanded_buffer);
		free(line);
	}
}

void	collect_heredoc(t_cmd *cmd, t_envnode **envp)
{
	t_output	*current;

	current = cmd->input2;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
			process_heredoc_entry(current, envp);
		current = current->next;
	}
}

void	handle_heredoc_if_needed(t_cmd *cmd)
{
	t_output	*current;
	int			fd;

	current = cmd->input2;
	while (current && current->type == TOKEN_HEREDOC)
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
		else
		{
			print_error("open", current->file, NULL);
			exit(1);
		}
		current = current->next;
	}
}
