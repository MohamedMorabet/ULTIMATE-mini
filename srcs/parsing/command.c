/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mest <oel-mest@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:27:28 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/20 01:58:04 by oel-mest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_command_tokens(t_ast *node, t_token **tokens, int inpar)
{
	int	ret;

	while (*tokens)
	{
		ret = process_single_token(node, tokens, inpar);
		if (ret == 1)
			return (1);
		if (ret == 2)
			break ;
	}
	return (0);
}

t_ast	*parse_command(t_token **tokens, int inpar)
{
	t_ast	*node;

	if (*tokens == NULL || is_special_token(*tokens) || (*tokens)->type == TOKEN_RPAREN)
	{
		if (*tokens == NULL)
			printf("4minishell: syntax error near unexpected token `newline'\n");
		else
			printf("5minishell: syntax error near unexpected token `%s'\n",
				(*tokens)->value);
		return (NULL);
	}
	node = create_ast_node(NODE_COMMAND, inpar);
	node->cmd = create_cmd_node();
	if (process_command_tokens(node, tokens, inpar))
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}