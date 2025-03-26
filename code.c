// #include "includes/minishell.h"
// #include "includes/execution.h"


// int execute_command(t_cmd *cmd, t_envnode **envp)
// {
// 	char **args;
// 	char *path;
// 	char **envp_array;
// 	int	status;


//     signal(SIGQUIT, SIG_IGN);
//     signal(SIGINT, SIG_IGN);
// 	// handle_wildcards(cmd);
// 	cmd->args = expand_line(cmd->args);	
// 	printf("args: %s\n", cmd->args);
// 	args = ft_split(cmd->args, ' ');
// 	if (args[0] == NULL)
// 		return (1);
// 	expand_env_vars2(&args, *envp);
// 	cmd->args = expand_env_vars(cmd->args, *envp);
// 	if (!args)
// 	{
// 		int saved_stdin = dup(STDIN_FILENO); // Save original stdin
// 		int saved_stdout = dup(STDOUT_FILENO); // Save original stdout
// 		if (cmd->output2)
// 		{
// 			redirect_output(cmd->output2, cmd->append);
// 		}
// 		if (cmd->input2)
// 		{
// 			if (redirect_input_noargs(cmd->input2) == 1)
// 				return (1);
// 		}
// 		dup2(saved_stdin, STDIN_FILENO); // Restore original stdin
// 		dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
// 		return (1);
// 	};
	
// 	// printf("args[0]: %s\n", args[0]);
// 	hundle_awk(args);
// 	// printf("args[0]: %s\n", args[0]);
// 	args[0] = remove_first_layer_quotes(args[0]);
// 	if (args[0])
// 	{
// 		if (is_builtin(args[0]))
// 		{
// 			int saved_stdin = dup(STDIN_FILENO); // Save original stdin
// 			int saved_stdout = dup(STDOUT_FILENO); // Save original stdout
// 			if (cmd->output2)
// 			{
// 				redirect_output(cmd->output2, cmd->append);
// 			}
// 			if (cmd->input2)
// 				redirect_input(cmd->input2);
// 			// if (cmd->output2)
// 			// 	printf("there is output2\n");
// 			int ret = run_builtin(args, envp, cmd);
// 			set_status(ret);
// 			free(args);
// 			dup2(saved_stdin, STDIN_FILENO); // Restore original stdin
// 			dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
// 			return ret;
// 		}
// 	}
// 	if (check_if_folder(args[0]) == 1)
// 	{
// 		if (args)
// 			free(args);
// 		return (1);
// 	}
// 	pid_t pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("minishell: fork");
// 		return (1);
// 		// exit(1);
// 	}
// 	path = NULL;
// 	if (args)
// 		path = search_command(args[0], *envp);
// 	envp_array = envp_to_array(*envp);
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		handle_heredoc_if_needed(cmd);
// 		if (cmd->output2)
// 		{
// 			// printf("output2: %s\n", cmd->output2->file);
// 			redirect_output(cmd->output2, cmd->append);
// 		}
// 			// redirect_multiple_outputs(cmd->output2, cmd->append);
// 		if (cmd->input2)
// 			redirect_input(cmd->input2);
// 		// if (strcmp(args[0], "") == 0)
// 		// {
// 		// 	printf("bash: : command not found\n");
// 		// 	if (args)
// 		// 		free(args);
// 		// 	exit (1);
// 		// }
// 		if (path)
// 		{
// 			// if (cmd->output2)
// 			// 	printf("there is output2\n");
// 			// if (cmd->output2)
// 			// 	redirect_multiple_outputs(cmd->output2, cmd->append);
// 			execve(path, args, envp_array);
// 		}
// 		else if (strncmp(args[0], "./", 2) == 0)  // Case 1: "./name"
//         {
//             execute_local_executable(args[0], args, envp_array);
//         }
// 		else
// 		{
// 			char *path0 = ft_getenv("$PATH", *envp);
// 			if (path0[0] == '\0')
// 			{
// 				size_t len = strlen(args[0]) + 3;  // Extra space for "./" + null terminator
// 				char *current_dir_exec = malloc(len);
// 				if (!current_dir_exec)
// 				{
// 					perror("malloc");
// 					exit(1);
// 				}

// 				strcpy(current_dir_exec, "./");  // Manually add "./"
// 				strcat(current_dir_exec, args[0]);

// 				if (access(current_dir_exec, F_OK) == 0)  // File exists
// 				{
// 					execute_local_executable(current_dir_exec, args, envp_array);
// 				}
// 				else
// 				{
// 					printf("bash: %s: No such file or directory\n", args[0]);
// 					if (args)
// 						free(args);
// 					if (path)
// 						free(path);
// 					exit(127);
// 				}
// 			}

// 			printf("bash: %s: command not found\n", args[0]);
// 			if (args)
// 				free(args);
// 			if (path)
// 				free(path);
// 			exit(127);
// 		}
// 	}
// 	waitpid(0, &g_status, 0);
// 	if (WIFSIGNALED(g_status))
// 	{
// 		if (WTERMSIG(g_status) == SIGINT)
// 			set_status(130);
// 		else if (WTERMSIG(g_status) == SIGQUIT)
// 			set_status(131);
// 	}
// 	else
// 		set_status(WEXITSTATUS(g_status));
// 	free(envp_array);
// 	unlink(cmd->heredoc);
// 	if (args)
// 		free(args);
// 	if (path)
// 		free(path);
// 	// printf("status: %d\n", WEXITSTATUS(g_status));
// 	if (g_status != 0)
// 		return (1);
// 	return (0);
// }





// int execute_command23(t_cmd *cmd, t_envnode **envp)
// {
// 	char **args;
// 	char *path;
// 	char **envp_array;
// 	int	status;


//     signal(SIGQUIT, SIG_IGN);
//     signal(SIGINT, SIG_IGN);
// 	// handle_wildcards(cmd);
// 	cmd->args = expand_line(cmd->args);	
// 	printf("args: %s\n", cmd->args);
// 	args = ft_split(cmd->args, ' ');
	
// 	expand_env_vars2(&args, *envp);
// 	cmd->args = expand_env_vars(cmd->args, *envp);
// 	if (!args)
// 	{
// 		int saved_stdin = dup(STDIN_FILENO); // Save original stdin
// 		int saved_stdout = dup(STDOUT_FILENO); // Save original stdout
// 		if (cmd->output2)
// 		{
// 			redirect_output(cmd->output2, cmd->append);
// 		}
// 		if (cmd->input2)
// 		{
// 			if (redirect_input_noargs(cmd->input2) == 1)
// 				return (1);
// 		}
// 		dup2(saved_stdin, STDIN_FILENO); // Restore original stdin
// 		dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
// 		return (1);
// 	};
// 	if (args[0] == NULL)
// 		return (1);
// 	// printf("args[0]: %s\n", args[0]);
// 	hundle_awk(args);
// 	// printf("args[0]: %s\n", args[0]);
// 	args[0] = remove_first_layer_quotes(args[0]);
// 	if (args[0])
// 	{
// 		if (is_builtin(args[0]))
// 		{
// 			int saved_stdin = dup(STDIN_FILENO); // Save original stdin
// 			int saved_stdout = dup(STDOUT_FILENO); // Save original stdout
// 			if (cmd->output2)
// 			{
// 				redirect_output(cmd->output2, cmd->append);
// 			}
// 			if (cmd->input2)
// 				redirect_input(cmd->input2);
// 			// if (cmd->output2)
// 			// 	printf("there is output2\n");
// 			int ret = run_builtin(args, envp, cmd);
// 			set_status(ret);
// 			free(args);
// 			dup2(saved_stdin, STDIN_FILENO); // Restore original stdin
// 			dup2(saved_stdout, STDOUT_FILENO); // Restore original stdout
// 			return ret;
// 		}
// 	}
// 	if (check_if_folder(args[0]) == 1)
// 	{
// 		if (args)
// 			free(args);
// 		return (1);
// 	}
// 	pid_t pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("minishell: fork");
// 		return (1);
// 		// exit(1);
// 	}
// 	path = NULL;
// 	if (args)
// 		path = search_command(args[0], *envp);
// 	envp_array = envp_to_array(*envp);
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_DFL);
// 		handle_heredoc_if_needed(cmd);
// 		if (cmd->output2)
// 		{
// 			// printf("output2: %s\n", cmd->output2->file);
// 			redirect_output(cmd->output2, cmd->append);
// 		}
// 			// redirect_multiple_outputs(cmd->output2, cmd->append);
// 		if (cmd->input2)
// 			redirect_input(cmd->input2);
// 		// if (strcmp(args[0], "") == 0)
// 		// {
// 		// 	printf("bash: : command not found\n");
// 		// 	if (args)
// 		// 		free(args);
// 		// 	exit (1);
// 		// }
// 		if (path)
// 		{
// 			// if (cmd->output2)
// 			// 	printf("there is output2\n");
// 			// if (cmd->output2)
// 			// 	redirect_multiple_outputs(cmd->output2, cmd->append);
// 			execve(path, args, envp_array);
// 		}
// 		else if (strncmp(args[0], "./", 2) == 0)  // Case 1: "./name"
//         {
//             execute_local_executable(args[0], args, envp_array);
//         }
// 		else
// 		{
// 			char *path0 = ft_getenv("$PATH", *envp);
// 			if (path0[0] == '\0')
// 			{
// 				size_t len = strlen(args[0]) + 3;  // Extra space for "./" + null terminator
// 				char *current_dir_exec = malloc(len);
// 				if (!current_dir_exec)
// 				{
// 					perror("malloc");
// 					exit(1);
// 				}

// 				strcpy(current_dir_exec, "./");  // Manually add "./"
// 				strcat(current_dir_exec, args[0]);

// 				if (access(current_dir_exec, F_OK) == 0)  // File exists
// 				{
// 					execute_local_executable(current_dir_exec, args, envp_array);
// 				}
// 				else
// 				{
// 					printf("bash: %s: No such file or directory\n", args[0]);
// 					if (args)
// 						free(args);
// 					if (path)
// 						free(path);
// 					exit(127);
// 				}
// 			}

// 			printf("bash: %s: command not found\n", args[0]);
// 			if (args)
// 				free(args);
// 			if (path)
// 				free(path);
// 			exit(127);
// 		}
// 	}
// 	waitpid(0, &g_status, 0);
// 	if (WIFSIGNALED(g_status))
// 	{
// 		if (WTERMSIG(g_status) == SIGINT)
// 			set_status(130);
// 		else if (WTERMSIG(g_status) == SIGQUIT)
// 			set_status(131);
// 	}
// 	else
// 		set_status(WEXITSTATUS(g_status));
// 	free(envp_array);
// 	unlink(cmd->heredoc);
// 	if (args)
// 		free(args);
// 	if (path)
// 		free(path);
// 	// printf("status: %d\n", WEXITSTATUS(g_status));
// 	if (g_status != 0)
// 		return (1);
// 	return (0);
// }