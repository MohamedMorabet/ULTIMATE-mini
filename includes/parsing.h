/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:23:37 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/26 02:32:14 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

typedef enum e_node_type {
    NODE_COMMAND,  // A single command with args (e.g., "echo hello")
    NODE_PIPE,     // A pipeline operator (|)
    NODE_AND,      // Logical AND (&&)
    NODE_OR,        // Logical OR (||)
    NODE_SUB
} t_node_type;

typedef struct s_output
{
    char *file;
    struct s_output *next;
}   t_output;

typedef struct s_cmd {
    char *args;    // Command arguments (string )
    char *input;    // File for input redirection (<)
    t_output    *input2;
    char *output;   // File for output redirection (>)
    t_output *output2;
    int append;     // 1 if >> (append), 0 if > (truncate)
    char *heredoc;  // Delimiter for heredoc (<<)
    t_output    *heredoc2;
} t_cmd;

typedef struct s_redi {
    t_output *input;
    t_output *output;
    t_output *heredoc;
    int append;
}   t_redi;

typedef struct s_ast {
    t_node_type type;     // COMMAND, PIPE, AND, OR, Subshell
    t_cmd *cmd;           // Only for command nodes
    t_redi *redi;
    struct s_ast *left;   // Left child (for &&, ||, or pipes)
    struct s_ast *right;  // Right child (for &&, ||, or pipes)
    int	inpar;
} t_ast;

int	process_single_token(t_ast *node, t_token **tokens, int inpar);
t_ast	*parse_command(t_token **tokens, int inpar);

t_ast	*parse_logical(t_token **tokens, int inpar);
t_ast	*parse(t_token *tokens);

t_ast	*parse_pipeline(t_token **tokens, int inpar);

int	parse_single_redirection(t_token **tokens, t_redi *redi);

t_ast	*handle_parentheses(t_token **tokens, int inpar);

t_ast   *create_ast_node(t_node_type type, int inpar);
t_cmd *create_cmd_node();
void add_argument(t_cmd *cmd, const t_token *token);
t_output    *create_output_node(char *file);
void    add_output(t_output **head, t_output *node);

int	is_special_token(t_token *token);
int	is_redirection_token(t_token *token);
int	is_word_or_quote(t_token_type type);


#endif