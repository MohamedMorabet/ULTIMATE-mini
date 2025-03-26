/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:39:52 by oel-mest          #+#    #+#             */
/*   Updated: 2025/03/26 03:21:28 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"

char *read_input(t_envnode *envp)
{
    char *line = NULL;

	line = readline("\033[1;32mbash-3.2$ \033[0m");
    if (!line)
    {
        free(line);
        free_env_list(envp);
        return NULL;
    }
    return (line);
}

void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line(); // Tell readline we moved to a new line
	rl_replace_line("", 0);
    rl_redisplay(); 
    set_status(1);
}

void    cheak_leaks(void)
{
    system("leaks minishell");
}

int main(int argc, char *argv[], char *envp[])
{
    t_envnode *head = parse_envp(envp);

    atexit(cheak_leaks);
    printf("\033[1;32mWelcome to Minishell\033[0m\n");
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    char *line = read_input(head);
	while(line != NULL)
	{
        add_history(line);
		t_token *tokens = tokenize(line);
		t_ast *ast = parse(tokens);
		free_tokens(tokens);
		free(line);
        minishell(ast, &head);
		free_ast(ast);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, SIG_IGN);
		line = read_input(head);
	}
    return EXIT_SUCCESS;
}
