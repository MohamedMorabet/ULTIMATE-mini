/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:10:53 by oel-mest          #+#    #+#             */
/*   Updated: 2025/04/03 14:43:13 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

t_token	*create_token(char *value, t_token_type type, int l_space)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	token->has_space = l_space;
	return (token);
}
