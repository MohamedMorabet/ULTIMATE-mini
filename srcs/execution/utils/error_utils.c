/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:34:40 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/25 20:32:43 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

void	print_error(char *first, ...)
{
	va_list	args;
	char	*str;

	write(2, "bash: ", 6);
	va_start(args, first);
	str = first;
	while (str != NULL)
	{
		write(2, str, ft_strlen(str));
		str = (char *)va_arg(args, char *);
	}
	va_end(args);
	write(2, "\n", 1);
}
