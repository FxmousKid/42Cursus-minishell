/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:38:01 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 21:18:54 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <unistd.h>

/* Checks if parent node redirects the same flow as the current node ;
 * if curr_node->token == REDIR_OUT && curr_node->parent_node->toke == (|, >>, >, ....)
 * then we return true, but if say curr_node = <, and parent_node = >, then false
 * return false if parent is Null */
bool	check_if_parent_same_flow(t_ast *node)
{
	if (!node->parent_node)
		return (false);
	if (node->token == REDIR_IN && node->parent_node->token == REDIR_IN)	
		return (true);
	if (is_tok_dual_cmd_type(node->token) || is_tok_redir_out_type(node->token))
	{
		if (is_tok_redir_out_type(node->parent_node->token))
			return (true);
		if (is_tok_dual_cmd_type(node->token))
			return (true);
	}
	return (false);
}

int	dup_or_cut_tree(t_ast *node, t_exec_data *e_data)
{
	if (check_if_parent_same_flow(node))
	{
		// call cut_tree;
		return (true);
	}
	if (node->token == REDIR_IN)
	{
		if (dup2(e_data->fd_in, STDIN_FILENO) < 0) 
			return (debug(DBG("Failed to dup2 stdout")), false);
	}
	else if (is_tok_redir_out_type(node->token))
	{
		if (dup2(e_data->fd_out, STDOUT_FILENO) < 0)
			return (debug(DBG("Failed to dup2 stdout")), false);
	}
	return (true);
}
