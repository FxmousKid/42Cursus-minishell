/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:57:26 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/09 19:56:32 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_process(t_data *data, t_ast *cmd)
{
	if (!access(cmd->ast_cmd.cmd, X_OK) == -1)
	{
		if (find_access(data, cmd->ast_cmd.cmd) == -1)
			return (debug(DBG("Failed to find the cmd")), 0);
	}
	execve(cmd->ast_cmd.cmd, cmd->ast_cmd.cmd_args, data->env);
	return (debug(DBG("function execve failed")), 0);
}

int	pipe_process(t_data *data, t_ast *pipe)
{
	
}

int	or_process(t_data *data, t_ast *or)
{
	if (find_process(data, or->ast_or.left) == 1)
		return (1);
	return (find_process(data, or->ast_or.right));
}

int	and_process(t_data *data, t_ast *and)
{
	if (find_process(data, and->ast_and.left) == 1)
		return (find_process(data, and->ast_and.right));
	return (0);
}