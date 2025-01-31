/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:29 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:45:43 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (e_data->fd_in > 0)
	{
		if (close(e_data->fd_in) < 0)
			debug(DBG("Failed to close fd_in"));
		e_data->fd_in = -1;
	}
	if (e_data->fd_out > 0)
	{
		if (close(e_data->fd_out) < 0)
			debug(DBG("Failed to close fd_out"));
		e_data->fd_out = -1;
	}
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
 *node -->  >		  b							pwd     b
 *		   /\
 *		  /  \
 *		 /    \
 *		pwd    a
 *
 * and all the correct free calls are called,
 * all the links between parent-child are adjusted
 *
 * return false if something failed to open
 * */
bool	cut_tree(t_ast **node, bool in_c, t_exec_data *e_data, t_data *data)
{
	if (!(*node)->parent_node || !need_to_cut_tree(*node))
	{
		if (in_c && !open_files(*node, e_data))
			return (debug(DBG("Failed to open_files()")), false);
		return (true);
	}
	while ((*node)->parent_node && need_to_cut_tree(*node))
	{
		if (in_c || (*node)->token == REDIR_IN)
		{
			if (!open_files(*node, e_data))
				return (debug(DBG("Failed to open_files()")), false);
			if (need_to_close_after_cut(*node))
				emergency_close_files(e_data);
		}
		(void)data;
		cut_tree_one_level_and_free(node);
	}
	if (!in_c && is_tok_dual_cmd_type((*node)->token))
		(*node)->status++;
	if (in_c && !open_files(*node, e_data))
		return (debug(DBG("Failed to open_files()")), false);
	return (true);
}

int	handle_redir(t_data *data, t_ast **node, t_exec_data *e_data)
{
	if (!cut_tree(node, true, e_data, data))
		exit_from_child("Failed to cut_curr_tree_level()", data);
	if (!is_tok_dual_cmd_type((*node)->token) && !dup_for_redir(*node, e_data))
	{
		emergency_close_files(e_data);
		exit_from_child("Failed to dup_or_cut_tree()", data);
	}
	*node = (*node)->left;
	return (true);
}
