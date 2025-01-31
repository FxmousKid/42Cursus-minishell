/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:36:08 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 17:42:10 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast_node(t_ast *node, int depth);

void	print_indentation(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
}

void	print_cmd_args(t_ast *node, int depth)
{
	int	i;
	int	j;

	i = 0;
	while (node->ast_cmd.cmd_args[i])
	{
		j = 0;
		while (j < depth + 1)
		{
			printf("  ");
			j++;
		}
		printf("arg[%d]: [%s]\n", i, node->ast_cmd.cmd_args[i]);
		i++;
	}
}

void	print_ast_node_2(t_ast *node, int depth)
{
	if (node->token == REDIR_IN)
	{
		printf("REDIR_IN\n");
		print_ast_node(node->ast_redir_in.left, depth + 1);
		print_ast_node(node->ast_redir_in.right, depth + 1);
	}
	else if (node->token == REDIR_OUT)
	{
		printf("REDIR_OUT\n");
		print_ast_node(node->ast_redir_out.left, depth + 1);
		print_ast_node(node->ast_redir_out.right, depth + 1);
	}
	else if (node->token == REDIR_APPEND)
	{
		printf("REDIR_APPEND\n");
		print_ast_node(node->ast_redir_append.left, depth + 1);
		print_ast_node(node->ast_redir_append.right, depth + 1);
	}
	else if (node->token == ERROR)
		printf("ERROR\n");
	else
		printf("UNKNOWN TOKEN: %d\n", node->token);
}

void	print_ast_node(t_ast *node, int depth)
{
	if (!node)
		return;
	print_indentation(depth);
	if (node->token == CMD)
	{
		printf("CMD: %s\n", node->ast_cmd.cmd_name);
		if (node->ast_cmd.cmd_args)
			print_cmd_args(node, depth);
	}
	else if (node->token == F_NAME)
		printf("FILE: %s\n", node->ast_file.file_name);
	else if (node->token == PIPE)
	{
		printf("PIPE\n");
		print_ast_node(node->ast_pipe.left, depth + 1);
		print_ast_node(node->ast_pipe.right, depth + 1);
	}
	else
		print_ast_node_2(node, depth);
}

void	print_ast(t_ast *root)
{
	if (!root)
	{
		printf("Empty AST\n");
		return;
	}
	while (root->parent_node)
		root = root->parent_node;
	printf("\n=== AST Structure ===\n");
	print_ast_node(root, 0);
	printf("===================\n\n");
}

