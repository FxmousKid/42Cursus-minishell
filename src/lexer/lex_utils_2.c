/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:28:14 by inazaria          #+#    #+#             */
/*   Updated: 2024/12/18 06:36:40 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>

bool	has_token(t_lexem *lexems, t_token token)
{
	int	lex_idx;

	lex_idx = 0;
	while (lexems[lex_idx].token != ERROR)
	{
		if (lexems[lex_idx].token == token)
			return (true);
		lex_idx++;
	}
	return (false);
}

bool	has_n_token(t_lexer *lex, t_token token, size_t n)
{
	size_t	idx;
	size_t	count;

	idx = 0;
	count = 0;
	while (idx < lex->lexem_count)
	{
		if (lex->lexems[idx].token == token)
			count++;
		idx++;
	}
	return (count == n);
}


void	swap_lexems(t_lexer *lex, size_t i, size_t j)
{
	t_lexem tmp;
	t_lexem *l1;
	t_lexem *l2;

	l1 = lex->lexems + i;
	l2 = lex->lexems + j;

	tmp.is_meta = l1->is_meta;
	tmp.token = l1->token;
	tmp.value = ft_strdup(l1->value);

	l1->is_meta = l2->is_meta;
	l1->token = l2->token;
	free(l1->value);
	l1->value = l2->value;

	l2->is_meta = tmp.is_meta;
	l2->token = tmp.token;
	l2->value = tmp.value;
}

void	offset_lexems_right(t_lexer *lex, size_t i)
{
	size_t	len;

	len = lex->lexem_count;
	while (len > i)
	{
		swap_lexems(lex, len, len - 1);
		len--;
	}
}

int	get_token_count(t_lexer lex, t_token token)
{
	size_t	idx;
	size_t	count;

	idx = 0;
	count = 0;
	while (idx < lex.lexem_count)
		count += lex.lexems[idx++].token == token;
	return (count);
}
