/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:36:08 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/02 05:32:23 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void print_ast_node(t_ast *node, int depth)
{
    if (!node)
        return;

    // Print indentation
    for (int i = 0; i < depth; i++)
        printf("  ");

    // Print node information based on token type
    switch (node->token)
    {
        case CMD:
            printf("CMD: %s\n", node->ast_cmd.cmd_name);
            if (node->ast_cmd.cmd_args)
            {
                for (int i = 0; node->ast_cmd.cmd_args[i]; i++)
                {
                    for (int j = 0; j < depth + 1; j++)
                        printf("  ");
                    printf("arg[%d]: %s\n", i, node->ast_cmd.cmd_args[i]);
                }
            }
            break;
        
        case F_NAME:
            printf("FILE: %s\n", node->ast_file.file_name);
            break;
        
        case PIPE:
            printf("PIPE\n");
            print_ast_node(node->ast_pipe.left, depth + 1);
            print_ast_node(node->ast_pipe.right, depth + 1);
            break;
        
        case REDIR_IN:
            printf("REDIR_IN\n");
            print_ast_node(node->ast_redir_in.left, depth + 1);
            print_ast_node(node->ast_redir_in.right, depth + 1);
            break;
        
        case REDIR_OUT:
            printf("REDIR_OUT\n");
            print_ast_node(node->ast_redir_out.left, depth + 1);
            print_ast_node(node->ast_redir_out.right, depth + 1);
            break;
        
        case REDIR_APPEND:
            printf("REDIR_APPEND\n");
            print_ast_node(node->ast_redir_append.left, depth + 1);
            print_ast_node(node->ast_redir_append.right, depth + 1);
            break;
        
        case AND:
            printf("AND\n");
            print_ast_node(node->ast_and.left, depth + 1);
            print_ast_node(node->ast_and.right, depth + 1);
            break;
        
        case OR:
            printf("OR\n");
            print_ast_node(node->ast_or.left, depth + 1);
            print_ast_node(node->ast_or.right, depth + 1);
            break;
		case ERROR:
			printf("ERROR\n");
			break;
        
        default:
            printf("UNKNOWN TOKEN: %d\n", node->token);
    }
}

void print_ast(t_ast *root)
{
    if (!root)
    {
        printf("Empty AST\n");
        return;
    }
    printf("\n=== AST Structure ===\n");
    print_ast_node(root, 0);
    printf("===================\n\n");
}
