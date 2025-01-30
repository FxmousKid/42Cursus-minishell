/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_child_easy_access.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:42:05 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/29 15:38:41 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_child_access_aux(t_ast *node)
{
	if (node->token == REDIR_APPEND)
	{
		node->left = node->ast_redir_append.left;
		node->right = node->ast_redir_append.right;
	}
	else if (node->token == OR)
	{
		node->left = node->ast_or.left;
		node->right = node->ast_or.right;
	}
	else if (node->token == AND)
	{
		node->left = node->ast_and.left;
		node->right = node->ast_and.right;
	}
}

void	set_child_access(t_ast *node)
{
	if (node->token == REDIR_OUT)
	{
		node->left = node->ast_redir_out.left;
		node->right = node->ast_redir_out.right;
	}
	else if (node->token == REDIR_IN)
	{
		node->left = node->ast_redir_in.left;
		node->right = node->ast_redir_in.right;
	}
	else if (node->token == PIPE)
	{
		node->left = node->ast_pipe.left;
		node->right = node->ast_pipe.right;
	}
	else 
		set_child_access_aux(node);
}



void	set_child_easy_access(t_ast *node)
{
	while (node->parent_node)
		node = node->parent_node;
	iterate_ast(node, set_child_access);
}
