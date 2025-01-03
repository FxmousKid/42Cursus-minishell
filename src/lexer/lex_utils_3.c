/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:48:21 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/02 21:48:51 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
