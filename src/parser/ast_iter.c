/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:13:11 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/03 01:18:21 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"


void	iterate_ast_aux(t_ast *ast, void (*f)(t_ast *ast))
{
	if (ast->token == REDIR_APPEND)
	{
		iterate_ast(ast->ast_redir_append.left, f);
		iterate_ast(ast->ast_redir_append.right, f);
	}
	if (ast->token == OR)
	{
		iterate_ast(ast->ast_or.left, f);
		iterate_ast(ast->ast_or.right, f);
	}
	if (ast->token == AND)
	{
		iterate_ast(ast->ast_and.left, f);
		iterate_ast(ast->ast_and.right, f);
	}
}

void	iterate_ast(t_ast *ast, void (*f)(t_ast *ast))
{
	if (!ast)
		return ;
	if (ast->token == CMD)
		f(ast);
	else if (ast->token == PIPE)
	{
		iterate_ast(ast->ast_pipe.left, f);
		iterate_ast(ast->ast_pipe.right, f);
	}
	else if (ast->token == REDIR_IN)
	{
		iterate_ast(ast->ast_redir_in.left, f);
		iterate_ast(ast->ast_redir_in.right, f);
	}
	else if (ast->token == REDIR_OUT)
	{
		iterate_ast(ast->ast_redir_out.left, f);
		iterate_ast(ast->ast_redir_out.right, f);
	}
	else
		iterate_ast_aux(ast, f);
}
