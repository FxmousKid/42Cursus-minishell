/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 05:20:22 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/28 17:46:00 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "exec.h"
#include "minishell.h"
#include <unistd.h>

bool	check_and_handle_pipe(t_data *data, t_ast **node, t_exec_data *e_data)
{	
	if ((*node)->token == PIPE)
	{
		if (!handle_pipe(*node, data, e_data))
			return (debug(DBG("Failed to handle_pipe()")), false);
		if ((*node)->status == 1)
			*node = (*node)->right;		
		else
			*node = (*node)->left;
	}
	// if ((*node)->token == CMD)
	// {
	// 	if ((*node)->parent_node && (*node)->parent_node->token == PIPE)
	// 		correct_pipe_dup(*node, data, e_data);
	// 	// check_and_exec_builtin(*node, data);
	// 	// data->cmd_count--;
	// 	return (true);
	// }
	return (false);
}

bool	check_and_handle_builtin_w_redir( \
	t_data *data,	t_ast **node, t_exec_data *e_data)
{
	int		og_stdout;

	if (is_tok_redir_type((*node)->token) && (*node)->left)
	{
		if (check_if_builtin((*node)->left))
		{
			if (!open_files(*node, e_data))
				return (debug(DBG("Failed to open_files()")), false);
			og_stdout = dup(STDOUT_FILENO);
			if (!dup_or_cut_tree(*node, e_data))
			{
				dup2(og_stdout, STDOUT_FILENO);
				close(og_stdout);
				emergency_close_files(e_data);
				return (debug(DBG("Failed to dup_or_cut_tree()")), false);
			}
			*node = (*node)->left;
			data->cmd_count--;
			check_and_exec_builtin(*node, data);
			return (dup2(og_stdout, STDOUT_FILENO), close(og_stdout), true);
		}
	}
	return (false);
}

int	handle_node(t_data *data, t_ast *node, t_exec_data *e_data)
{
	if (check_and_exec_builtin(node, data))
		return (true);
	else if (check_and_handle_pipe(data, &node, e_data))
		return (true);
	else if (check_and_handle_builtin_w_redir(data, &node, e_data))
		return (true);
	data->pids[data->cmd_idx] = fork();
	if (data->pids[data->cmd_idx] < 0)
		return (debug(DBG("Failed to fork()")), false);
	if (data->pids[data->cmd_idx] != 0)
		return (true);
	if (is_tok_redir_type(node->token))
	{
		handle_redir(data, node, e_data);
		node = node->left;
	}
	else if (node->parent_node && node->parent_node->token == PIPE)
		correct_pipe_dup(node, data, e_data);
	exec_cmd(node, data, e_data);
	return (1);
}

int	exec_loop(t_data *data)
{
	t_ast		*node;
	t_exec_data	exec_data;
	int			og_cmd_count;
	
	node = data->ast;
	og_cmd_count = data->cmd_count;
	ft_bzero(&exec_data, sizeof(t_exec_data));
	if (node->parent_node)
		node = node->parent_node;
	while (node && data->cmd_idx < og_cmd_count)
	{
		if (node && node->status == 2)
			node = node->parent_node;
		if (!node)
			break;
		handle_node(data, node, &exec_data);
		close_prev_command_fds(&exec_data);
		data->cmd_idx++;
		if (node)
			node->status++;
	}
	return (close_e_data(&exec_data), true);
}
