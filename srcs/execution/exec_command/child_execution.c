/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:55:57 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/26 02:16:54 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

static void	handle_empty_path(t_exec_ctx *ctx)
{
	size_t	len;
	char	*current_dir_exec;

	len = strlen(ctx->args[0]) + 3;
	current_dir_exec = malloc(len);
	if (!current_dir_exec)
	{
		print_error("malloc", NULL);
		exit(1);
	}
	strcpy(current_dir_exec, "./");
	strcat(current_dir_exec, ctx->args[0]);
	if (access(current_dir_exec, F_OK) == 0)
		execute_local_executable(current_dir_exec, ctx->args, ctx->envp_array);
	print_error(ctx->args[0], ": No such file or directory", NULL);
	if (ctx->args)
		free(ctx->args);
	if (ctx->path)
		free(ctx->path);
	exit(127);
}

static void	child_handle_no_path(t_exec_ctx *ctx)
{
	char	*path0;

	path0 = ft_getenv("$PATH", *(ctx->envp));
	if (!path0)
	{
		handle_empty_path(ctx);
	}
	print_error(ctx->args[0], ": command not found", NULL);
	if (ctx->args)
		free(ctx->args);
	if (ctx->path)
		free(ctx->path);
	if (path0)
		free(path0);
	exit(127);
}

void	child_process(t_exec_ctx *ctx)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_heredoc_if_needed(ctx->cmd);
	if (ctx->cmd->output2)
	{
		if (redirect_output(ctx->cmd->output2, ctx->cmd->append))
			exit(1);
	}
	if (ctx->cmd->input2)
	{
		if (redirect_input(ctx->cmd->input2))
			exit(1);
	}
	if (ctx->path)
		execve(ctx->path, ctx->args, ctx->envp_array);
	else if (strncmp(ctx->args[0], "./", 2) == 0)
		execute_local_executable(ctx->args[0], ctx->args, ctx->envp_array);
	else
		child_handle_no_path(ctx);
}
