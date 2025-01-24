/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:48:21 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 20:25:55 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <stdbool.h>

int	get_token_count_to_idx_n(t_lexer lex, int n, t_token tok)
{
	int	idx;
	int	count;

	idx = 0;
	count = 0;
	while (lex.lexems[idx].token != ERROR && idx < n)
	{
		if (lex.lexems[idx].token == tok)
			count++;
		idx++;
	}
	return (count);
}

bool	is_tok_redir_type(t_token tok)
{
	bool	res;

	res = (tok == REDIR_APPEND);
	res |= (tok == REDIR_OUT);
	res |= (tok == REDIR_IN);
	return (res);
}

bool	is_tok_dual_cmd_type(t_token tok)
{
	bool	res;

	res = (tok == PIPE);
	res |= (tok == AND);
	res |= (tok == OR);
	return (res);
}

bool	is_tok_redir_out_type(t_token tok)
{
	bool	res;

	res = (tok == REDIR_OUT);
	res |= (tok == REDIR_APPEND);
	return (res);
}
