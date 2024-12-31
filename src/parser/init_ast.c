/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:55:44 by inazaria          #+#    #+#             */
/*   Updated: 2024/12/31 18:37:21 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <stdio.h>

/* get the idx of the 1st meta-character, else returns the idx to the 
 * first lexem */

size_t	get_real_starting_idx_for_node_creation(t_lexer lex)
{
	size_t	lex_idx;

	lex_idx = 0;
	while (lex_idx < lex.lexem_count)
	{
		if (lex.lexems[lex_idx].is_meta)
			return (lex_idx);
		lex_idx++;
	}
	return (0);
}

int	get_cmd_arg_count(t_lexer lex)
{
	size_t	lex_idx;
	int		arg_count;
	t_lexem	lexem;

	lex_idx = 0;
	while (lex_idx < lex.lexem_count)
	{
		if (lex.lexems[lex_idx].token == CMD)
		{
			lex_idx++;
			break ;
		}
		lex_idx++;
	}
	arg_count = 0;
	lexem = lex.lexems[lex_idx];
	while (lexem.token == DQ_WORD || lexem.token == SQ_WORD)
	{
		arg_count++;
		lex_idx++;
		lexem = lex.lexems[lex_idx];
	}
	return (arg_count);
}

/* We allocate sizeof(char *) * (arg_count + 2), why 2 ? 1 for the
 * command name, and one for a NULL byte
 * We start arg_idx at 1 because in this function we assume the 1st lexem 
 * is a command */

bool	fill_first_cmd_node(t_data *data)
{
	int					arg_count;
	int					arg_idx;
	t_lexem				*lexems;			
	struct s_ast_cmd	*ast_cmd;

	data->ast->parent_node = NULL;
	data->ast->token = CMD;
	ast_cmd = &data->ast->ast_cmd;
	ast_cmd->cmd_name = ft_strdup(data->lex.lexems[0].value);
	arg_count = get_cmd_arg_count(data->lex);
	ast_cmd->cmd_args = ft_calloc(sizeof(char *), arg_count + 2);
	if (!ast_cmd->cmd_args)
		return (debug(DBG("Failed to allocate cmd_args")), false);
	arg_idx = 1;
	lexems = data->lex.lexems;
	while (arg_count-- > 0)
	{
		ast_cmd->cmd_args[arg_idx - 1] = ft_strdup(lexems[arg_idx].value);
		arg_idx++;
	}
	return (true);
}

bool	fill_ast(t_data *data)
{
	size_t	lex_idx;

	lex_idx = get_real_starting_idx_for_node_creation(data->lex);
	if (lex_idx == 0)
	{
		if (!fill_first_cmd_node(data))
			return (debug(DBG("Failed to fill_first_cmd_node()")), false);
		return (true);
	}
	while (lex_idx < data->lex.lexem_count)
	{
		if (data->lex.lexems[lex_idx].token == CMD)
		{

		}
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
	
	print_ast(data->ast);
	printf("\n");

	return (true);
}
