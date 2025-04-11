/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mest <oel-mest@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:39:52 by oel-mest          #+#    #+#             */
/*   Updated: 2025/04/11 17:15:45 by oel-mest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"

char	*read_input(t_envnode *envp)
{
	char	*line;

	line = NULL;
	line = readline("\033[1;32mHHHH$ \033[0m");
	if (!line)
	{
		free(line);
		free_env_list(envp);
		return (NULL);
	}
	return (line);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay(); 
	set_status(1);
}

void	check_leaks(void)
{
	system("leaks minishell");
}

void	ft_add_history(char *line)
{
	if (line && *line)
	{
		add_history(line);
	}
}

int	main(int argc __unused, char *argv[] __unused, char *envp[])
{
	t_envnode	*head;
	char		*line;
	t_token		*tokens;
	t_ast		*ast;

	// atexit(check_leaks);
	head = parse_envp(envp);
	// printf("\033[1;32mWelcome to Minishell\033[0m\n");
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	line = read_input(head);
	while (line != NULL)
	{
		ft_add_history(line);
		tokens = tokenize(line);
		ast = parse(tokens);
		free_tokens(tokens);
		free(line);
		// print_ast_tree(ast, head);
		minishell(ast, &head);
		// print_ast_tree(ast, head);
		free_ast(ast);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		line = read_input(head);
	}
	return (EXIT_SUCCESS);
}
