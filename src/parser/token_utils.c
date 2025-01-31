/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:27:33 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/30 19:31:16 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

/* this function assumes a parent exists for the passed node */

bool	need_to_cut_tree(t_ast *node)
{
	t_token tok1;
	t_token	tok2;

	tok1 = node->token;
	tok2 = node->parent_node->token;
	if (is_tok_dual_cmd_type(tok1))
		return (false); 
	if (tok1 == tok2)
		return (true);
	if (tok1 == REDIR_IN && is_tok_redir_out_type(tok2))
		return (true);
	if (is_tok_redir_out_type(tok1) && is_tok_redir_out_type(tok2))
		return (true);
	if (tok1 == REDIR_IN && is_tok_dual_cmd_type(tok2))
		return (true);
	return (false);
}

/* this function assumes a parent exists for the passed node */

bool	need_to_close_after_cut(t_ast *node)
{
	t_token tok1;
	t_token	tok2;

	tok1 = node->token;
	tok2 = node->parent_node->token;

	if (tok1 == tok2)
		return (true);
	if (is_tok_redir_out_type(tok1) && is_tok_redir_out_type(tok2))
		return (true);
	return (false);
}
