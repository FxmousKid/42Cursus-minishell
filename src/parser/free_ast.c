/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 00:45:18 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/29 15:37:47 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_leaf(t_ast *node)
{
	if (node->token == CMD)
	{
		free(node->ast_cmd.cmd_name);
		free_split(node->ast_cmd.cmd_args);
	}
	else if (node->token == F_NAME)
		free(node->ast_file.file_name);
	free(node);
}

/* frees the AST starting from the leftmost node (a leaf) */

void	free_ast(t_ast *leftmost_node)
{
	if (!leftmost_node)
		return ;
	while (leftmost_node->parent_node)
		leftmost_node = leftmost_node->parent_node;
	iterate_ast(leftmost_node, free_leaf);
}
