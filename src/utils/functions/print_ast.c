/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:36:08 by inazaria          #+#    #+#             */
/*   Updated: 2024/12/31 17:56:49 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void print_ast_indent(int depth) {
    for (int i = 0; i < depth; i++)
        printf("  ");
}

void print_ast_recursive(t_ast *ast, int depth) {
    if (!ast) return;

    print_ast_indent(depth);
    
    switch (ast->token) {
        case CMD:
            printf("CMD: %s\n", ast->ast_cmd.cmd_name);
            if (ast->ast_cmd.cmd_args) {
                print_ast_indent(depth + 1);
                printf("Args:");
				for (int i = 0; ast->ast_cmd.cmd_args[i]; i++)
					printf(" %s", ast->ast_cmd.cmd_args[i]);
            }
            break;
			
        case PIPE:
            printf("PIPE |\n");
            print_ast_indent(depth + 1);
            printf("Left:\n");
            print_ast_recursive(ast->ast_pipe.left, depth + 2);
            print_ast_indent(depth + 1);
            printf("Right:\n");
            print_ast_recursive(ast->ast_pipe.right, depth + 2);
            break;
        case REDIR_IN:
            printf("REDIR IN <\n");
            print_ast_indent(depth + 1);
            printf("Left:\n");
            print_ast_recursive(ast->ast_redin_in.left, depth + 2);
            print_ast_indent(depth + 1);
            printf("Right:\n");
            print_ast_recursive(ast->ast_redin_in.right, depth + 2);
            break;
        case REDIR_OUT:
            printf("REDIR OUT >\n");
            print_ast_indent(depth + 1);
            printf("Left:\n");
            print_ast_recursive(ast->ast_redir_out.left, depth + 2);
            print_ast_indent(depth + 1);
            printf("Right:\n");
            print_ast_recursive(ast->ast_redir_out.right, depth + 2);
            break;
        case REDIR_APPEND:
            printf("REDIR APPEND >>\n");
            print_ast_indent(depth + 1);
            printf("Left:\n");
            print_ast_recursive(ast->ast_redir_append.left, depth + 2);
            print_ast_indent(depth + 1);
            printf("Right:\n");
            print_ast_recursive(ast->ast_redir_append.right, depth + 2);
            break;
        case AND:
            printf("AND &&\n");
            print_ast_indent(depth + 1);
            printf("Left:\n");
            print_ast_recursive(ast->ast_and.left, depth + 2);
            print_ast_indent(depth + 1);
            printf("Right:\n");
            print_ast_recursive(ast->ast_and.right, depth + 2);
            break;
        case OR:
            printf("OR ||\n");
            print_ast_indent(depth + 1);
            printf("Left:\n");
            print_ast_recursive(ast->ast_or.left, depth + 2);
            print_ast_indent(depth + 1);
            printf("Right:\n");
            print_ast_recursive(ast->ast_or.right, depth + 2);
            break;
       default:
            printf("Unknown token type: %d\n", ast->token);
    }
}

void print_ast(t_ast *ast) {
    printf("Abstract Syntax Tree:\n\n");
    print_ast_recursive(ast, 0);
}
