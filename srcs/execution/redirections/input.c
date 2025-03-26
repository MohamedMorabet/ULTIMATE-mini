/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:20:13 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/25 20:20:22 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

static int	open_last_input_file(t_output *input_list)
{
	int			fd;
	t_output	*current;

	fd = -1;
	current = input_list;
	while (current)
	{
		if (fd != -1)
			close(fd);
		fd = open(current->file, O_RDONLY | O_CLOEXEC);
		if (fd < 0)
		{
			print_error(current->file, ": No such file or directory", NULL);
			return (-1);
		}
		current = current->next;
	}
	return (fd);
}

int	redirect_input(t_output *input_list)
{
	int	fd;

	fd = open_last_input_file(input_list);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		print_error("dup2 input file", NULL);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
