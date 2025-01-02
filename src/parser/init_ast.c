/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:55:44 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/02 06:07:52 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>

int	get_cmd_arg_count(t_lexem *lexems, int start_idx)
{
	int	cmd_args_count;

	cmd_args_count = 0;
	while (lexems[start_idx].token != ERROR)
	{
		if (lexems[start_idx].token != WORD &&
			lexems[start_idx].token != SQ_WORD &&
			lexems[start_idx].token != DQ_WORD)
			break;
		cmd_args_count++;
		start_idx++;
	}
	return (cmd_args_count);
}

/* We allocate sizeof(char *) * (arg_count + 2), why 2 ? 1 for the
 * command name, and one for a NULL byte
 * We start arg_idx at 1 because in this function we assume the 1st lexem 
 * is a command */

bool	fill_cmd_node(t_ast *ast_child, t_lexer lex, int cmd_idx)
{
	int					arg_count;
	struct s_ast_cmd	*ast_cmd;
	int					idx;

	ast_child->token = CMD;
	ast_cmd = &ast_child->ast_cmd;
	ast_cmd->cmd_name = ft_strdup(lex.lexems[cmd_idx].value);
	arg_count = get_cmd_arg_count(lex.lexems, cmd_idx + 1);
	ast_cmd->cmd_args = ft_calloc(sizeof(char *), arg_count + 2);
	if (!ast_cmd->cmd_args)
		return (debug(DBG("Failed to allocate cmd_args")), false);
	idx = 0;
	ast_cmd->cmd_args[idx++] = ft_strdup(lex.lexems[cmd_idx++].value);
	while (arg_count-- > 0)
	{
		ast_cmd->cmd_args[idx] = ft_strdup(lex.lexems[cmd_idx].value);
		cmd_idx++;
		idx++;
	}
	ast_cmd->cmd_args[idx] = NULL;
	return (true);
}

/* makes it so that the parent links to the child
 * allocates a rchild for the node using ft_calloc
 * if metachar has a file on it's rchild (>, <, >>, ...) then fill struct details
 * */

bool	fill_relation(t_ast **ast_lchild, t_lexem *lexems, int idx, t_token tok)
{
	t_ast	*ast_rchild;

	ast_rchild = ft_calloc(sizeof(t_ast), 1);
	if (!ast_rchild)
		return (debug(DBG("Failed to allocate ast_right")), false);
	ast_rchild->parent_node = (*ast_lchild)->parent_node;
	if (tok == PIPE)
	{
		(*ast_lchild)->parent_node->ast_pipe.right = ast_rchild;
		(*ast_lchild)->parent_node->ast_pipe.left = *ast_lchild;
		(*ast_lchild) = ast_rchild;
	}
	if (tok == REDIR_IN)
	{
		(*ast_lchild)->parent_node->ast_redir_in.right = ast_rchild;
		(*ast_lchild)->parent_node->ast_redir_in.left = *ast_lchild;
	}
	if (tok == REDIR_OUT)
	{
		(*ast_lchild)->parent_node->ast_redir_out.right = ast_rchild;
		(*ast_lchild)->parent_node->ast_redir_out.left = *ast_lchild;
	}
	if (tok == REDIR_APPEND)
	{
		(*ast_lchild)->parent_node->ast_redir_append.right = ast_rchild;
		(*ast_lchild)->parent_node->ast_redir_append.left = *ast_lchild;
	}
	if (tok == REDIR_IN || tok == REDIR_OUT || tok == REDIR_APPEND)
	{
		ast_rchild->token = lexems[idx + 1].token;
		ast_rchild->ast_file.file_name = ft_strdup(lexems[idx + 1].value);
	}
	return (true);
}


bool	fill_metachar_node(t_ast **ast_lchild, t_lexer lex, int arg_idx)
{
	t_lexem *lexems;
	t_token	tok;

	lexems = lex.lexems;
	(*ast_lchild)->parent_node = ft_calloc(sizeof(t_ast), 1);
	if (!(*ast_lchild)->parent_node)
		return (debug(DBG("Failed to allocate parent node")), false);
	tok = lexems[arg_idx].token;
	(*ast_lchild)->parent_node->token = tok;
	if (!fill_relation(ast_lchild, lexems, arg_idx, tok))
	{
		free((*ast_lchild)->parent_node);
		return (debug(DBG("Failed to fill_relation()")), false);
	}
	return (true);
}

/* After being passed to fill_metachar_node, ast_tmp will be on the right child */

bool	fill_ast(t_data *data)
{
	int		lex_idx;
	t_ast	*ast_tmp;

	ast_tmp = data->ast;
	if (!data->lex.lexems[0].is_meta)
	{
		if (!fill_cmd_node(ast_tmp, data->lex, 0))
			return (debug(DBG("Failed to fill_first_cmd_node()")), false);
	}
	lex_idx = get_next_tok_idx(data->lex.lexems, ERROR, 1, true);
	while (lex_idx < (int) data->lex.lexem_count && lex_idx != -1)
	{
		if (!fill_metachar_node(&ast_tmp, data->lex, lex_idx))
			return (debug(DBG("Failed to fill_metachar_node()")), false);
		lex_idx = get_next_tok_idx(data->lex.lexems, CMD, lex_idx, false);
		if (lex_idx == -1)
			break ;
		printf("lex_idx: %d\n", lex_idx);
		if (!fill_cmd_node(ast_tmp, data->lex, lex_idx))
			return (debug(DBG("Failed to fill_cmd_node()")), false);
		lex_idx = get_next_tok_idx(data->lex.lexems, ERROR, lex_idx, true);
		ast_tmp = ast_tmp->parent_node;
		print_ast(ast_tmp);

	}
	return (true);
}

bool	init_and_fill_ast(t_data *data)
{
	t_ast	*ast_root;

	ast_root = ft_calloc(sizeof(t_ast), 1);
	if (!ast_root)
		return (debug(DBG("Failed to allocate t_ast")), false);
	data->ast = ast_root;
	if (!fill_ast(data))
		return (free(ast_root), debug(DBG("Failed to fill_ast()")), false);
	

	
	printf("\n");
	if (ast_root->parent_node)
		ast_root = ast_root->parent_node;
	// print_ast(ast_root);
	printf("%s", ast_root->ast_pipe.right->ast_cmd.cmd_name);
	printf("\n");

	return (true);
}
