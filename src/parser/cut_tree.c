/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:13:30 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/30 13:50:16 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
 * all the correct free calls are called,
 * all the links between parent-child are adjusted
*/

static void	modif_s_ast_left_child(t_ast *parent, t_ast *new_child)
{
	if (parent->token == REDIR_IN)
	{
		parent->ast_redir_in.left = new_child;
		parent->left = new_child;
	}
	else if (parent->token == REDIR_OUT)
	{
		parent->ast_redir_out.left = new_child;
		parent->left = new_child;
	}
	else if (parent->token == REDIR_APPEND)
	{
		parent->ast_redir_append.left = new_child;
		parent->left = new_child;
	}
	else if (parent->token == PIPE)
	{
		parent->ast_pipe.left = new_child;
		parent->left = new_child;
	}
}

void	cut_tree_one_level_and_free(t_ast **node)
{
	t_ast *old_node;

	if (!(*node)->parent_node)
		return ;
	(*node)->left->parent_node = (*node)->parent_node;
	modif_s_ast_left_child((*node)->parent_node, (*node)->left);
	old_node = *node;
	*node = (*node)->parent_node;
	free(old_node->right->ast_file.file_name);
	free(old_node->right);
	free(old_node);
}
