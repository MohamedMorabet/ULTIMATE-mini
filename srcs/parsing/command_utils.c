/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:31:31 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/26 02:33:58 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_word_or_quote(t_cmd **cmd, t_token **tokens)
{
	add_argument ((*cmd), *tokens);
	*tokens = (*tokens)->next;
}

static int	handle_redirect_in(t_cmd **cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	
	if (*tokens && is_word_or_quote((*tokens)->type))
	{
		free ((*cmd)->input);
		//(*cmd)->input = ft_strdup ((*tokens)->value);
		add_output (&(*cmd)->input2, create_output_node((*tokens)->value));
		*tokens = (*tokens)->next;
		return (0);
	}
	else if (*tokens == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline\'\n");
		return (1);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s\'\n", (*tokens)->value);
		return (1);
	}
}

static int	handle_redirect_out(t_cmd **cmd, t_token **tokens)
{
	int	is_append;

	is_append = ((*tokens)->type == TOKEN_APPEND);
	*tokens = (*tokens)->next;
	if (*tokens && is_word_or_quote((*tokens)->type))
	{
		free ((*cmd)->output);
		(*cmd)->output = ft_strdup ((*tokens)->value);
		add_output (&(*cmd)->output2, create_output_node((*tokens)->value));
		(*cmd)->append = is_append;
		*tokens = (*tokens)->next;
		return (0);
	}
	else if (*tokens == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline\'\n");
		return (1);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s\'\n", (*tokens)->value);
		return (1);
	}
}

static int	handle_heredoc(t_cmd **cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	if (*tokens && is_word_or_quote((*tokens)->type))
	{
		free ((*cmd)->heredoc);
		//(*cmd)->heredoc = ft_strdup ((*tokens)->value);
		add_output (&(*cmd)->heredoc2, create_output_node((*tokens)->value));
		*tokens = (*tokens)->next;
		return (0);
	}
	else if (*tokens == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline\'\n");
		return (1);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s\'\n", (*tokens)->value);
		return (1);
	}
	return (0);
}

int	process_single_token(t_ast *node, t_token **tokens, int inpar)
{
	t_token	*cur = *tokens;

	if (is_word_or_quote(cur->type))
		handle_word_or_quote(&node->cmd, tokens);
	else if (cur->type == TOKEN_REDIRECT_IN)
		return (handle_redirect_in(&node->cmd, tokens));
	else if (cur->type == TOKEN_REDIRECT_OUT || cur->type == TOKEN_APPEND)
		return (handle_redirect_out(&node->cmd, tokens));
	else if (cur->type == TOKEN_HEREDOC)
		return (handle_heredoc(&node->cmd, tokens));
	else if (cur->type == TOKEN_LPAREN)
		return (printf("10minishell: syntax error near unexpected token `%s'\n",
				cur->value), 1);
	else if (cur->type == TOKEN_RPAREN && !inpar)
		return (printf("11minishell: syntax error near unexpected token `%s'\n",
				cur->value), 1);
	else
		return (2);
	return (0);
}
