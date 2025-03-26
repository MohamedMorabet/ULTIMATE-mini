/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:49:25 by mel-mora          #+#    #+#             */
/*   Updated: 2025/03/25 22:17:23 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

int	is_builtin(char *cmd)
{
	return (
		!strcmp(cmd, "echo")
		|| !strcmp(cmd, "cd")
		|| !strcmp(cmd, "pwd")
		|| !strcmp(cmd, "export")
		|| !strcmp(cmd, "unset")
		|| !strcmp(cmd, "env")
		|| !strcmp(cmd, "exit")
		|| !strcmp(cmd, "correction")
	);
}

int	builtin_correction(void)
{
	printf("HHHH: ser awa t9awd ser\n");
	set_status(0);
	return (0);
}

int	run_builtin(t_exec_ctx	*ctx)
{
	if (!strcmp(ctx->args[0], "echo"))
		return (builtin_echo(ctx->cmd->args));
	else if (!strcmp(ctx->args[0], "cd"))
		return (builtin_cd(ctx->args, ctx->envp));
	else if (!strcmp(ctx->args[0], "pwd"))
		return (builtin_pwd());
	else if (!strcmp(ctx->args[0], "export"))
		return (builtin_export(ctx->args, ctx->envp));
	else if (!strcmp(ctx->args[0], "unset"))
		return (builtin_unset(ctx->args, ctx->envp));
	else if (!strcmp(ctx->args[0], "env"))
		return (builtin_env(*(ctx->envp)));
	else if (!strcmp(ctx->args[0], "exit"))
		return (builtin_exit(ctx));
	else if (!strcmp(ctx->args[0], "correction"))
		return (builtin_correction());
	return (1);
}
