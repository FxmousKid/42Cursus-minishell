/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 05:20:22 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 20:57:58 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "exec.h"
#include "minishell.h"


int	handle_node(t_data *data, t_ast *node, t_exec_data *e_data)
{
	// if (node->token == PIPE)
	// 	// to verify later
	// 	(void) data;
	// 	// handle_pipe(node, data, e_data);
	//

	data->pids[data->cmd_idx] = fork();
	if (data->pids[data->cmd_idx] < 0)
		return (debug(DBG("Failed to fork()")), false);
	if (data->pids[data->cmd_idx] != 0)
		return (true);

	// if we're here it means we're in the child
	
	if (is_tok_redir_type(node->token))
	{
		handle_redir(data, node, e_data);
		node = node->left;
	}
	exec_cmd(node, data, e_data);
	
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

	
	while (node)
	{
		handle_node(data, node, &exec_data);
		data->cmd_idx++;
		node = node->parent_node;
	}

	return (true);
}
