/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:22:53 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/25 20:28:16 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

#define HEREDOC_FILE "/tmp/minihell_heredoc"

static void	write_heredoc_content(char *delimiter)
{
	char	buffer[1024];
	int		fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc temp file");
		exit(1);
	}
	while (1)
	{
		printf("> ");
		if (!fgets(buffer, sizeof(buffer), stdin))
			break ;
		if (strncmp(buffer, delimiter, strlen(delimiter)) == 0
			&& buffer[strlen(delimiter)] == '\n')
			break ;
		write(fd, buffer, strlen(buffer));
	}
	close(fd);
}

static void	redirect_heredoc_input(void)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_RDONLY);
	if (fd < 0)
	{
		perror("reopen heredoc file");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_heredoc(char *delimiter)
{
	write_heredoc_content(delimiter);
	redirect_heredoc_input();
}
