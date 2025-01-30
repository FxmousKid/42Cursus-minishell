/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:29 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/29 22:53:21 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	open_files(t_ast *node, t_exec_data *e_data)
{
	char	*file_name;

	file_name = node->right->ast_file.file_name;
	if (node->token == REDIR_IN)
		e_data->fd_in = open(file_name, O_RDONLY);
	else if (node->token == REDIR_OUT)
		e_data->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token == REDIR_APPEND)
		e_data->fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (e_data->fd_in < 0)
		debug(DBG("Failed to open file for reading"));
	else if (e_data->fd_out < 0)
		debug(DBG("Failed to open file for writing"));
	if (e_data->fd_in < 0 || e_data->fd_out < 0)
	{
		custom_name_perror(file_name);
		return (false);
	}
	return (true);
}

void	emergency_close_files(t_exec_data *e_data)
{
	if (e_data->fd_out)
		close(e_data->fd_out);
	else if (e_data->fd_in)
		close(e_data->fd_in);
}

/* This function will be both called in the child and the parent,
 * in order to "cut" the tree to the same status in both process.
 *
 * Takes the addr of the node, and 'cuts' the current level :
 *
 *
 *				 >					  node -->		>
 *			   /   \							   / \
 *			  /     \			becomes		      /   \
 *           /       \						     /     \
 *node --> >		  b							pwd     b
 *		   /\
 *		  /  \
 *		 /    \
 *		pwd    a
 *
 * and all the correct free calls are called,
 * all the links between parent-child are adjusted
 *
 * */
bool	cut_curr_tree_level(t_ast **node, bool in_child, t_exec_data e_data)
{
	(void)e_data;
	(void)in_child;

	if (!(*node)->parent_node)
		return (false);

	while ((*node)->parent_node)
	{
		// if (in_child && !open_files(*node, e_data))
		//		return (debug(DBG("Failed to open_files()")), false);
		//

		
	}
	
	// *node = (*node)->parent_node;
	return (true);
}

int	handle_redir(t_data *data, t_ast *node, t_exec_data *e_data)
{
	// while ()
	//{
	//	if (!open_files(node, e_data))
	//		exit_from_child("Failed to open_files()", data);
	// 	cut_curr_tree_level(&node);
	//}

	if (!open_files(node, e_data))
		exit_from_child("Failed to open_files()", data);
	if (!dup_or_cut_tree(node, e_data))
	{
		emergency_close_files(e_data);
		exit_from_child("Failed to dup_or_cut_tree()", data);
	}
	node = node->left;
	return (true);
}
