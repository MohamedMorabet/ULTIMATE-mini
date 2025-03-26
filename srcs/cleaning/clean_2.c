/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:31:03 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/25 22:21:34 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ast(t_ast *ast)
{
	if (!ast)
		return;
	free_ast(ast->left);
	free_ast(ast->right);
	if (ast->cmd)
		free_cmd(ast->cmd);
	if (ast->type == NODE_SUB)
		free_redi(ast->redi);
	free(ast);
}

void	free_split(char **split)
{
	int i = 0;
    if (!split || !*split)
        return;
	while (split[i])
		free(split[i++]);
	free(split);
}
