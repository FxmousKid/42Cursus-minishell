/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:54:47 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/24 20:27:07 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdbool.h>

bool	is_escaped(char *str)
{
	if (str[0] == '\\' && str[1] == '\'')
		return (true);
	if (str[0] == '\\' && str[1] == '"')
		return (true);
	return (false);
}

void	quote_conditions(char c, bool *in_dq, bool *in_sq)
{
	if (c == '"' && !*in_dq && !*in_sq)
		*in_dq = true;
	else if (c == '"' && *in_dq)
		*in_dq = false;
	if (c == '\'' && !*in_dq && *in_sq)
		*in_sq = false;
	else if (c == '\'' && !*in_dq && !*in_sq)
		*in_sq = true;
}

int	count_words_mod(char *str, char *sep)
{
	int		wc;
	bool	fchange;
	bool	in_dq;
	bool	in_sq;

	wc = 0;
	fchange = 1;
	in_dq = false;
	in_sq = false;
	while (*str)
	{
		wc += (fchange && !is_occ_aux(*str, sep));
		fchange = (is_occ_aux(*str, sep) && !in_dq && !in_sq);
		quote_conditions(*str, &in_dq, &in_sq);
		if (!*(str + 1))
			wc += fchange && is_occ_aux(*str, sep);
		if (is_escaped(str))
			str++;
		str++;
	}
	printf("wordcount = %d\n", wc);
	return (wc);
}
