/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:55:44 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 12:01:56 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"

/* before allocating we check if the child has a parent already allocated,
 * this basically checks if we're on the left child or right child, and we 
 * need that to know to allocate a grandparent and not overwrite the current 
 * parent */

bool	fill_metachar_node(t_ast **ast_child, t_lexer lex, int arg_idx)
{
	t_lexem	*lexems;
	t_token	tok;

	lexems = lex.lexems;
	if ((*ast_child)->parent_node)
		(*ast_child) = (*ast_child)->parent_node;
	(*ast_child)->parent_node = ft_calloc(sizeof(t_ast), 1);
	if (!(*ast_child)->parent_node)
		return (debug(DBG("Failed to allocate parent node")), false);
	tok = lexems[arg_idx].token;
	(*ast_child)->parent_node->token = tok;
	if (!fill_relation(ast_child, lexems, arg_idx, tok))
	{
		free((*ast_child)->parent_node);
		return (debug(DBG("Failed to fill_relation()")), false);
	}
	return (true);
}

bool	fill_current_node(t_ast **lchild, t_data *data, int curr_lex_idx)
{
	if (data->lex.lexems[curr_lex_idx].is_meta)
	{
		if (!fill_metachar_node(lchild, data->lex, curr_lex_idx))
			return (debug(DBG("Failed to fill_metachar_node()")), false);
	}
	else if (data->lex.lexems[curr_lex_idx].token == CMD)
	{
		if (!fill_cmd_node(*lchild, data, curr_lex_idx))
			return (debug(DBG("Failed to fill_cmd_node()")), false);
	}
	return (true);
}

bool	fill_ast(t_data *data)
{
	int		lex_idx;
	t_ast	*ast_tmp;

	ast_tmp = data->ast;
	lex_idx	 = get_next_cmd_or_metachar_idx(data->lex.lexems, 0);
	while (lex_idx < (int) data->lex.lexem_count && lex_idx != -1)
	{
		if (!fill_current_node(&ast_tmp, data, lex_idx))
			return (debug(DBG("Failed to fill_current_node()")), false);
		lex_idx = get_next_cmd_or_metachar_idx(data->lex.lexems, lex_idx + 1);
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
	set_child_easy_access(ast_root);
	return (true);
}
