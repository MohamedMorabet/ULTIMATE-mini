/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mora <mel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:49:25 by mel-mora          #+#    #+#             */
/*   Updated: 2025/04/05 16:06:58 by mel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/execution.h"

int	is_builtin(char *cmd)
{
	return (
		!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "correction")
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
	if (!ft_strcmp(ctx->args[0], "echo"))
		return (builtin_echo(ctx->cmd->args));
	else if (!ft_strcmp(ctx->args[0], "cd"))
		return (builtin_cd(ctx->args, ctx->envp));
	else if (!ft_strcmp(ctx->args[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(ctx->args[0], "export"))
		return (builtin_export(ctx->args, ctx->envp));
	else if (!ft_strcmp(ctx->args[0], "unset"))
		return (builtin_unset(ctx->args, ctx->envp));
	else if (!ft_strcmp(ctx->args[0], "env"))
		return (builtin_env(*(ctx->envp)));
	else if (!ft_strcmp(ctx->args[0], "exit"))
		return (builtin_exit(ctx));
	else if (!ft_strcmp(ctx->args[0], "correction"))
		return (builtin_correction());
	return (1);
}
