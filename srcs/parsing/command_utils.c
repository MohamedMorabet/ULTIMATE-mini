/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:31:31 by oel-mest          #+#    #+#             */
/*   Updated: 2025/04/10 22:50:01 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_word_or_quote2(t_cmd **cmd, t_token **tokens)
{
	add_argument ((*cmd), *tokens);
	*tokens = (*tokens)->next;
}

static int	handle_redirect_in2(t_cmd **cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	if (*tokens && is_word_or_quote((*tokens)->type))
	{
		add_output (&(*cmd)->input2, create_output_node((*tokens)->value,
				TOKEN_REDIRECT_IN));
		*tokens = (*tokens)->next;
		while (*tokens && is_word_or_quote((*tokens)->type)
			&& !(*tokens)->has_space)
		{
			join_output ((*cmd)->input2, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		return (0);
	}
	else if (*tokens == NULL)
	{
		print_error("syntax error near unexpected token `newline\'", NULL);
		return (set_status(258), 1);
	}
	else
	{
		print_error("syntax error near unexpected token `",
			(*tokens)->value, "\'", NULL);
		return (set_status(258), 1);
	}
}

static int	handle_redirect_out2(t_cmd **cmd, t_token **tokens)
{
	int	is_append;

	is_append = ((*tokens)->type == TOKEN_APPEND);
	*tokens = (*tokens)->next;
	if (*tokens && is_word_or_quote((*tokens)->type))
	{
		free ((*cmd)->output);
		(*cmd)->output = ft_strdup ((*tokens)->value);
		add_output (&(*cmd)->output2, create_output_node((*tokens)->value,
				TOKEN_APPEND));
		(*cmd)->append = is_append;
		*tokens = (*tokens)->next;
		while (*tokens && is_word_or_quote((*tokens)->type)
			&& !(*tokens)->has_space)
		{
			join_output ((*cmd)->output2, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		return (0);
	}
	else if (*tokens == NULL)
		return (print_error("syntax error near unexpected token `newline\'",
				NULL), set_status(258), 1);
	else
		return (print_error("syntax error near unexpected token `",
				(*tokens)->value, "\'", NULL), set_status(258), 1);
}

static int	handle_heredoc2(t_cmd **cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	if (*tokens && is_word_or_quote((*tokens)->type))
	{
		add_output (&(*cmd)->input2, create_output_node((*tokens)->value,
				TOKEN_HEREDOC));
		*tokens = (*tokens)->next;
		while (*tokens && is_word_or_quote((*tokens)->type)
			&& !(*tokens)->has_space)
		{
			join_output ((*cmd)->input2, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		return (0);
	}
	else if (*tokens == NULL)
	{
		print_error("syntax error near unexpected token `newline\'", NULL);
		return (set_status(258), 1);
	}
	else
		return (print_error("syntax error near unexpected token `",
				(*tokens)->value, "\'", NULL), set_status(258), 1);
	return (0);
}

int	process_single_token(t_ast *node, t_token **tokens, int inpar)
{
	t_token	*cur;

	cur = *tokens;
	if (is_word_or_quote(cur->type))
		handle_word_or_quote2(&node->cmd, tokens);
	else if (cur->type == TOKEN_REDIRECT_IN)
		return (handle_redirect_in2(&node->cmd, tokens));
	else if (cur->type == TOKEN_REDIRECT_OUT || cur->type == TOKEN_APPEND)
		return (handle_redirect_out2(&node->cmd, tokens));
	else if (cur->type == TOKEN_HEREDOC)
		return (handle_heredoc2(&node->cmd, tokens));
	else if (cur->type == TOKEN_LPAREN)
		return (print_error("syntax error near unexpected token `",
				cur->value, "\'", NULL), set_status(258), 1);
	else if (cur->type == TOKEN_RPAREN && !inpar)
		return (print_error("syntax error near unexpected token `",
				cur->value, "\'", NULL), set_status(258), 1);
	else
		return (2);
	return (0);
}
