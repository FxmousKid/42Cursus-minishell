/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:22:31 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/03 00:44:29 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <stdint.h>

int	get_cmd_arg_count(t_lexem *lexems, int start_idx)
{
	int	cmd_args_count;

	cmd_args_count = 0;
	while (lexems[start_idx].token != ERROR)
	{
		if (lexems[start_idx].token != WORD \
			&& lexems[start_idx].token != SQ_WORD \
			&& lexems[start_idx].token != DQ_WORD \
			&& lexems[start_idx].token != ENV_VAR \
			&& lexems[start_idx].token != HEREDOC)
			break ;
		cmd_args_count++;
		start_idx++;
	}
	return (cmd_args_count);
}

/* This function should only be called when you're sure that command 
 * argument is located at the given lexem index, because it doesn't check 
 * and assumes that it's the case 
 * extracts the env variable when necessary
 * */

char	*get_arg_value(t_data *data, int cmd_lexem_idx)
{
	int		hdoc_num;
	t_lexem *lexems;

	lexems = data->lex.lexems;
	if (lexems[cmd_lexem_idx].token != HEREDOC)
		return (extract_str_or_env_var(lexems[cmd_lexem_idx], data));
	hdoc_num = 0;
	if (lexems[cmd_lexem_idx + 1].token == Q_LIMITER)
	{
		hdoc_num = get_token_count_to_idx_n(data->lex, cmd_lexem_idx, Q_LIMITER); 
		return (expand_env_var_in_str(data->heredocs_dq[hdoc_num], data));
	}
	else if (lexems[cmd_lexem_idx + 1].token == LIMITER)
	{
		hdoc_num = get_token_count_to_idx_n(data->lex, cmd_lexem_idx, LIMITER);
		return (expand_env_var_in_str(data->heredocs[hdoc_num], data));
	}
	return (NULL);
}


/* We allocate sizeof(char *) * (arg_count + 2), why 2 ? 1 for the
 * command name, and one for a NULL byte
 * We start arg_idx at 1 because in this function we assume the 1st lexem 
 * is a command */

bool	fill_cmd_node(t_ast *ast_child, t_data *data, int cmd_idx)
{
	int					arg_count;
	struct s_ast_cmd	*ast_cmd;
	int					idx;

	ast_child->token = CMD;
	ast_cmd = &(ast_child->ast_cmd);
	ast_cmd->cmd_name = extract_str_or_env_var(data->lex.lexems[cmd_idx], data);
	arg_count = get_cmd_arg_count(data->lex.lexems, cmd_idx + 1);
	ast_cmd->cmd_args = ft_calloc(sizeof(char *), arg_count + 2);
	if (!ast_cmd->cmd_args)
		return (debug(DBG("Failed to allocate cmd_args")), false);
	idx = 0;
	ast_cmd->cmd_args[idx++] = get_arg_value(data, cmd_idx++);
	while (arg_count-- > 0)
		ast_cmd->cmd_args[idx++] = get_arg_value(data, cmd_idx++);
	ast_cmd->cmd_args[idx] = NULL;
	return (true);
}

/* makes it so that the parent links to the child
 * allocates a rchild for the node using ft_calloc
 * if metachar has a file on it's rchild (>, <, >>, ...) then fill struct details
 * */

static bool	fill_redirection(t_ast **lchild, t_ast *rchild, t_token tok)
{
	if (tok == REDIR_IN)
	{
		(*lchild)->parent_node->ast_redir_in.right = rchild;
		(*lchild)->parent_node->ast_redir_in.left = *lchild;
	}
	if (tok == REDIR_OUT)
	{
		(*lchild)->parent_node->ast_redir_out.right = rchild;
		(*lchild)->parent_node->ast_redir_out.left = *lchild;
	}
	if (tok == REDIR_APPEND)
	{
		(*lchild)->parent_node->ast_redir_append.right = rchild;
		(*lchild)->parent_node->ast_redir_append.left = *lchild;
	}
	return (true);
}

bool	fill_relation(t_ast **lchild, t_lexem *lexems, int idx, t_token tok)
{
	t_ast	*rchild;

	rchild = ft_calloc(sizeof(t_ast), 1);
	if (!rchild)
		return (debug(DBG("Failed to allocate ast_right")), false);
	rchild->parent_node = (*lchild)->parent_node;
	if (tok == PIPE || tok == AND || tok == OR)
	{
		(*lchild)->parent_node->ast_pipe.right = rchild;
		(*lchild)->parent_node->ast_pipe.left = *lchild;
		(*lchild) = rchild;
	}
	else if (tok == REDIR_IN || tok == REDIR_OUT || tok == REDIR_APPEND)
	{
		fill_redirection(lchild, rchild, tok);
		rchild->token = lexems[idx + 1].token;
		rchild->ast_file.file_name = ft_strdup(lexems[idx + 1].value);
		*lchild = (*lchild)->parent_node;
	}
	return (true);
}
