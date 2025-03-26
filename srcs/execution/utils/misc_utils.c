/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:36:29 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/26 00:31:25 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

int	is_quoted_delimiter(const char *delimiter)
{
	if (!delimiter)
		return (0);
	return (delimiter[0] == '"' || delimiter[0] == '\'');
}

// envp to array (dont malloc)
char	**envp_to_array(t_envnode *envp)
{
	int			i;
	t_envnode	*tmp;
	char		**envp_array;
	char		*tmp2;

	i = 0;
	tmp = envp;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp_array = malloc(sizeof(char *) * (i + 1));
	if (!envp_array)
		return (NULL);
	i = 0;
	tmp = envp;
	while (tmp)
	{
		envp_array[i] = ft_strjoin(tmp->var, "=");
		tmp2 = envp_array[i];
		envp_array[i] = ft_strjoin(envp_array[i], tmp->value);
		free(tmp2);
		i++;
		tmp = tmp->next;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

static void	process_first_arg(char **arg)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(*arg);
	if (len == 2 && (((*arg)[0] == '"' && (*arg)[1] == '"') ||
		((*arg)[0] == '\'' && (*arg)[1] == '\'')))
	{
		tmp = ft_strdup("");
		free(*arg);
		*arg = tmp;
	}
}

static void	process_quoted_arg(char **arg)
{
	char	*new_str;
	size_t	len;
	char	quote;

	quote = (*arg)[0];
	if ((quote == '\'' || quote == '"') && (*arg)[1] != quote)
	{
		len = ft_strlen(*arg);
		if (len > 1 && (*arg)[len - 1] == quote)
		{
			new_str = ft_substr(*arg, 1, len - 2);
			free(*arg);
			*arg = new_str;
		}
	}
}

void	hundle_awk(char **args)
{
	int	i;

	if (!args)
		return ;
	process_first_arg(&args[0]);
	i = 0;
	while (args[i])
	{
		process_quoted_arg(&args[i]);
		i++;
	}
}
