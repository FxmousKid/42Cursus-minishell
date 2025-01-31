/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:48:54 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 17:20:46 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_status_one(t_ast *node, t_data *data, t_exec_data *e_data)
{
	if (e_data->pipefd[1] && close(e_data->pipefd[1]) < 0)
		return (debug(DBG("Failed to close pipefd[1]")), false);
	e_data->pipefd[1] = -1;
	if (node->parent_node && node->parent_node->token == PIPE)
	{
		if (pipe(e_data->pipefd) < 0)
			return (debug(DBG("Failed to pipe()")), false);
		if (data->cmd_idx > 1)
			if (close(e_data->old_read_fds[data->cmd_idx - 1]) < 0)
				return (debug(DBG("Failed to close old_read_fds")), false);
		node->parent_node->status = 1;
	}
	if (node->parent_node && is_tok_redir_type(node->parent_node->token))
	{
		if (!cut_tree(&node->parent_node, true, e_data, data))
			return (debug(DBG("Failed to cut_curr_tree_level()")), false);
	}
	return (true);
}

int	handle_pipe_parent(t_ast *node, t_data *data, t_exec_data *e_data)
{
	if (node->status == 0 && pipe(e_data->pipefd) < 0)
		return (debug(DBG("Failed to pipe()")), false);
	if (node->status == 1)
		if (!handle_status_one(node, data, e_data))
			return (debug(DBG("Failed to handle_status_one()")), false);
	if (data->cmd_idx != data->cmd_count - 1)
	{
		e_data->old_read_fds[data->cmd_idx + 1] = dup(e_data->pipefd[0]);
		if (close(e_data->pipefd[0]) < 0)
			return (debug(DBG("Failed to close pipefd[0]")), false);
		e_data->pipefd[0] = -1;
		if (node->left && is_tok_redir_out_type(node->left->token))
		{
			if (close(e_data->pipefd[1]) < 0)
				return (debug(DBG("Failed to close pipefd[1]")), false);
			e_data->pipefd[1] = -1;
		}
	}
	return (true);
}

int	dup_stdout_pipe_correct(t_ast *node, t_exec_data *e_data)
{
	if (!node->parent_node->parent_node)
		(void)node;
	else if (node->parent_node->parent_node->token == PIPE)
	{
		if (dup2(e_data->pipefd[1], STDOUT_FILENO) < 0)
			return (debug(DBG("Failed to dup stdout")), false);
		if (close(e_data->pipefd[1]) < 0)
			return (debug(DBG("Failed to close pipefd[1]")), false);
	}
	if (e_data->fd_out)
	{
		fflush(stderr);
		if (dup2(e_data->fd_out, STDOUT_FILENO) < 0)
			return (debug(DBG("Failed to dup stdout")), false);
		if (close(e_data->fd_out) < 0)
			return (debug(DBG("Failed to close pipefd[1]")), false);
	}
	return (true);
}

int handle_dup_status_zero(t_data *data, t_exec_data *e_data)
{
	if (e_data->old_read_fds[data->cmd_idx + 1])
		if (close(e_data->old_read_fds[data->cmd_idx + 1]) < 0)
			return (debug(DBG("Failed to close old_read_fds")), false);
	if (e_data->pipefd[1] && dup2(e_data->pipefd[1], STDOUT_FILENO) < 0)
		return (debug(DBG("Failed to dup stdin")), false);
	if (e_data->pipefd[1] && close(e_data->pipefd[1]) < 0)
		return (debug(DBG("Failed to close pipefd[1]")), false);
	if (e_data->fd_in != 0)
	{
		if (dup2(e_data->fd_in, STDIN_FILENO) < 0)
			return (debug(DBG("Failed to dup2 stdin")), false);
		if (close(e_data->fd_in) < 0)
			return (debug(DBG("Failed to close stdnin")), false);
	}
	return (true); 
}

int	correct_pipe_dup(t_ast *node, t_data *data, t_exec_data *e_data)
{
	// if we're on the left node
	if (node->parent_node->status == 0)
	{
		if (!handle_dup_status_zero(data, e_data))
			return (debug(DBG("Failed to dup_stdin_pipe_correct()")), false);
	}
	// if we're on the right node
	else if (node->parent_node->status == 1)
	{
		if (e_data->old_read_fds[data->cmd_idx + 1])
			if (close(e_data->old_read_fds[data->cmd_idx + 1]) < 0)
				return (debug(DBG("Failed to close old_read_fds")), false);
		if (e_data->old_read_fds[data->cmd_idx])
			if (dup2(e_data->old_read_fds[data->cmd_idx], STDIN_FILENO) < 0)
				return (debug(DBG("Failed to dup stdin")), false);
		if (e_data->old_read_fds[data->cmd_idx])
			if (close(e_data->old_read_fds[data->cmd_idx]) < 0)
				return (debug(DBG("Failed to close old_read_fds")), false);
		if (!dup_stdout_pipe_correct(node, e_data))
			return (debug(DBG("Failed to dup_stdout_pipe_correct()")), false);
	}
	return (true);
}
