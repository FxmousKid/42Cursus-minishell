/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:57:26 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/18 19:39:13 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_process(t_data *data, t_ast *cmd)
{
	pid_t	pid;

	printf("fd[0] : %d\n", data->fd[0]);
	if (cmd->ast_cmd.in_fd == -1 && cmd->ast_cmd.out_fd == -1)
	{
		pipe(data->pipe);
		cmd->ast_cmd.out_fd = data->pipe[1];
		cmd->ast_cmd.in_fd = data->fd[0];
	}
	if (cmd->ast_cmd.in_fd == -1)
		cmd->ast_cmd.in_fd = data->fd[0];
	printf("cmd : %s : in_fd = %d out_fd = %d\n", cmd->ast_cmd.cmd, cmd->ast_cmd.in_fd, cmd->ast_cmd.out_fd);
	pid = fork();
	if (pid < 0)
		return (perror(""), debug(DBG("Error pid cmd_process()")), -1);
	if (pid == 0)
	{
		dup2(cmd->ast_cmd.in_fd, STDIN_FILENO);
		dup2(cmd->ast_cmd.out_fd, STDOUT_FILENO);
		if (exec_cmd(data, cmd) == -1)
			return (-1);
	}
	else
	{
		data->fd[0] = data->pipe[0];
		data->fd[1] = data->pipe[1];
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	exec_cmd(t_data *data, t_ast *cmd)
{
	if (access(cmd->ast_cmd.cmd, X_OK) == -1)
	{
		cmd->ast_cmd.cmd = find_access(data, cmd->ast_cmd.cmd);
		if (cmd->ast_cmd.cmd == NULL)
			return (ft_putstr_fd("command not found: ", 2),
				ft_putstr_fd(cmd->ast_cmd.cmd, 2), ft_putstr_fd("\n", 2),
				debug(DBG("Failed to find the cmd")), 0);
	}
	execve(cmd->ast_cmd.cmd, cmd->ast_cmd.cmd_args, data->envir);
	return (perror(""), debug(DBG("function execve failed")), 0);
}

int	pipe_process(t_data *data, t_ast *pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror(""), debug(DBG("Error pid pipe_process()")), -1);
	if (pid == 0)
	{
		find_process(data, pipe->ast_pipe.left);
	}
	else
	{
		find_process(data, pipe->ast_pipe.right);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	or_process(t_data *data, t_ast *or)
{
	if (find_process(data, or->ast_or.left) == 0)
		return (0);
	return (find_process(data, or->ast_or.right));
}

int	and_process(t_data *data, t_ast *and)
{
	if (find_process(data, and->ast_and.left) == 0)
		return (find_process(data, and->ast_and.right));
	return (0);
}
