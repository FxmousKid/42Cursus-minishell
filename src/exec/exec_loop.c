/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 05:20:22 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:42:49 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_pipe(t_data *data, t_ast **node, t_exec_data *e_data)
{
	if ((*node)->token == REDIR_IN)
	{
		if (!cut_tree(node, false, e_data, data))
			return (debug(DBG("Failed to cut_tree()")), false);
	}
	if ((*node)->token == PIPE)
	{
		if (!handle_pipe_parent(*node, data, e_data))
			return (debug(DBG("Failed to handle_pipe()")), false);
		if ((*node)->parent_node && (*node)->parent_node->token == PIPE)
			(*node)->parent_node->status = 1;
	}
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
			if (!cut_tree(node, true, e_data, data))
				return (debug(DBG("Failed to cut_curr_tree_level()")), false);
			og_stdout = dup(STDOUT_FILENO);
			if (!dup_for_redir(*node, e_data))
			{
				dup2(og_stdout, STDOUT_FILENO);
				close(og_stdout);
				emergency_close_files(e_data);
				return (debug(DBG("Failed to dup_or_cut_tree()")), false);
			}
			*node = (*node)->left;
			check_and_exec_builtin(*node, data);
			return (dup2(og_stdout, STDOUT_FILENO), close(og_stdout), true);
		}
	}
	return (false);
}

int	handle_node(t_data *data, t_ast **node, t_exec_data *e_data)
{
	if (handle_pipe(data, node, e_data))
		return (true);
	data->pids[data->cmd_idx] = fork();
	if (data->pids[data->cmd_idx] < 0)
		return (debug(DBG("Failed to fork()")), false);
	if (data->pids[data->cmd_idx] != 0)
		return (cut_tree(node, false, e_data, data), true);
	if ((*node)->status == 1 && is_tok_dual_cmd_type((*node)->token))
		*node = (*node)->right;
	else if ((*node)->status == 0 && is_tok_dual_cmd_type((*node)->token))
		*node = (*node)->left;
	if ((*node)->parent_node && (*node)->parent_node->token == PIPE)
		correct_pipe_dup(*node, data, e_data);
	else if (is_tok_redir_type((*node)->token))
		handle_redir(data, node, e_data);
	exec_cmd(*node, data, e_data);
	return (1);
}

int	exec_loop(t_data *data)
{
	t_ast		*node;
	t_exec_data	exec_data;

	node = data->ast;
	ft_bzero(&exec_data, sizeof(t_exec_data));
	if (node->parent_node)
		node = node->parent_node;
	while (node && data->cmd_idx < data->cmd_count)
	{
		if (node && node->status == 2)
			node = node->parent_node;
		if (!node)
			break ;
		handle_node(data, &node, &exec_data);
		data->cmd_idx++;
		if (node)
			node->status++;
	}
	return (close_e_data(&exec_data), true);
}
