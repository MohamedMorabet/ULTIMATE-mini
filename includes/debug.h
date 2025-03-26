/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mest <oel-mest@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:38:07 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/20 01:48:49 by oel-mest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"

void print_indentation(int depth, int is_last);
void print_cmd(t_cmd *cmd, int depth, int is_last, t_envnode *head);
void print_ast(t_ast *node, int depth, int is_last, t_envnode *head);
void print_ast_tree(t_ast *root, t_envnode *head);
void print_tokens(t_token *tokens);
void    print_outputs(t_output *head);
#endif