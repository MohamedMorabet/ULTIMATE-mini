/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:51:40 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/26 00:22:24 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_envnode {
	char				*var;
	char				*value;
	struct s_envnode	*next;
}	t_envnode;

char    *ft_getenv(char *name, t_envnode *head);
t_envnode *parse_envp(char **envp);

char	*expand_env_vars(char *args, t_envnode *env_list);
char    **expand_env_vars2(char **args, t_envnode *env_list);

char    *handle_lstatus_var();
#endif