/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 05:20:22 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/14 00:03:34 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "exec.h"
#include "minishell.h"


/* One important thing to check for is the presence of a built-in the child node.
 * Why ? Because we won't fork if it's the case. */

int	handle_node(t_data *data, t_ast *node, t_exec_data *e_data)
{
	check_to_open_pipe(node, e_data);
	// if (cmd_node_is_builtin(node))
		// data->pids[data->cmd_idx] = fork();
	data->pids[data->cmd_idx] = fork(); // to remove
 	if (data->pids[data->cmd_idx] < 0)
		return (debug(DBG("Failed to fork()")), false);
	if (data->pids[data->cmd_idx] != 0) // if not child proc
		return (true);
	// if we're here it means we're the child proc
	


	
	check_to_open_files(node, e_data);
	if (data->cmd_idx == data->cmd_count - 1)
		exit(1);
	exit(0);
	return (true);
}

int	exec_loop(t_data *data)
{
	t_ast		*node;
	t_exec_data	exec_data;
	
	node = data->ast;
	ft_bzero(&exec_data, sizeof(t_exec_data));
	if (node->parent_node)
		node = node->parent_node;

	printf("Hello from exec_loop !\n");
	
	while (node)
	{
		handle_node(data, node, &exec_data);
		node = node->parent_node;
		data->cmd_idx++;
	}

	return (true);
}
