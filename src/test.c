/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:58:53 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/21 19:18:29 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_ast	*test_cmd(t_data *data, t_ast *ast)
{
	ast = malloc(sizeof(t_ast) * 1);
	ast->token = PIPE;
	data->ast = ast;

	ast->ast_pipe.left = malloc(sizeof(t_ast) * 1);
	ast->ast_pipe.right = malloc(sizeof(t_ast) * 1);

	ast->ast_pipe.left->token = CMD;
	ast->ast_pipe.left->ast_cmd.cmd = "cat";
	ast->ast_pipe.left->ast_cmd.cmd_args = malloc(sizeof(char *)* 3);
	ast->ast_pipe.left->ast_cmd.cmd_args[0] = "cat";
	ast->ast_pipe.left->ast_cmd.cmd_args[1] =  NULL;
	ast->ast_pipe.left->ast_cmd.cmd_args[2] = NULL;
	ast->ast_pipe.left->ast_cmd.in_fd = -1;
	ast->ast_pipe.left->ast_cmd.out_fd = -1;

	ast->ast_pipe.right->token = CMD;
	ast->ast_pipe.right->ast_cmd.cmd = "ls";
	ast->ast_pipe.right->ast_cmd.cmd_args = malloc(sizeof(char *)* 3);
	ast->ast_pipe.right->ast_cmd.cmd_args[0] = "ls";
	ast->ast_pipe.right->ast_cmd.cmd_args[1] = NULL;
	ast->ast_pipe.right->ast_cmd.cmd_args[2] = NULL;
	ast->ast_pipe.right->ast_cmd.in_fd = -1;
	ast->ast_pipe.right->ast_cmd.out_fd = 1;
	return (ast);
}

void	print_ast(t_ast *ast)
{
	int	i;

	i = 1;
	if (ast->token == PIPE)
	{
		print_ast(ast->ast_pipe.left);
		printf(" | ");
		print_ast(ast->ast_pipe.right);
		printf("\n");
	}
	else if (ast->token == AND)
	{
		print_ast(ast->ast_pipe.left);
		printf(" && ");
		print_ast(ast->ast_pipe.right);
		printf("\n");
	}
	else if (ast->token == OR)
	{
		print_ast(ast->ast_pipe.left);
		printf(" || ");
		print_ast(ast->ast_pipe.right);
		printf("\n");
	}
	else if (ast->token == CMD)
	{
		printf("%s ", ast->ast_cmd.cmd);
		while (ast->ast_cmd.cmd_args[i])
		{
			printf("%s ", ast->ast_cmd.cmd_args[i]);
			i++;
		}
	}
}