/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:49:38 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/25 20:01:40 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

void	print_env_export(t_envnode *envp, char **args)
{
	int			i;
	t_envnode	*node;

	i = 0;
	if (!args[1])
	{
		while (envp)
		{
			if (envp->value)
				printf("declare -x %s=\"%s\"\n", envp->var, envp->value);
			else
				printf("declare -x %s\n", envp->var);
			envp = envp->next;
		}
	}
}

char	*strip_quotes(const char *s)
{
	char	*res;
	char	*temp;
	size_t	len;

	res = strdup(s);
	while (res)
	{
		len = strlen(res);
		if (len < 2)
			break ;
		if ((res[0] == '"' && res[len - 1] == '"')
			|| (res[0] == '\'' && res[len - 1] == '\''))
		{
			temp = strndup(res + 1, len - 2);
			free(res);
			res = temp;
		}
		else
			break ;
	}
	return (res);
}

int	process_export_arg_no_eq(char *arg, t_envnode **envp)
{
	t_envnode	*node;
	int			valid;

	valid = is_valid_var_name(arg);
	if (valid == 0)
	{
		print_error("minishell: export: ", arg,
			": not a valid identifier", NULL);
		set_status(1);
		return (1);
	}
	node = find_env_var(*envp, arg);
	if (node == NULL)
	{
		node = create_node(arg);
		node->value = NULL;
		add_node(envp, node);
	}
	return (0);
}

char	*extract_var_name(char *arg, size_t *var_len)
{
	char	*eq;

	eq = strchr(arg, '=');
	*var_len = (size_t)(eq - arg);
	return (strndup(arg, *var_len));
}

int	update_export_var(char *var_name, char *arg, t_envnode **envp)
{
	t_envnode	*node;
	char		*value;
	char		*stripped;

	value = strdup(strchr(arg, '=') + 1);
	stripped = strip_quotes(value);
	free(value);
	node = find_env_var(*envp, var_name);
	if (node != NULL)
	{
		free(node->value);
		node->value = stripped;
	}
	else
	{
		node = create_node(arg);
		node->value = stripped;
		add_node(envp, node);
	}
	return (0);
}
