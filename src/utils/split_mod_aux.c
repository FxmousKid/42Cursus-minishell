/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:54:47 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/17 23:43:47 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline bool	is_escaped(char *str)
{
	if (str[0] == '\\' && str[1] == '\'')
		return (true);
	if (str[0] == '\\' && str[1] == '"')
		return (true);
	return (false);
}

static inline void	quote_conditiions(char c, bool *in_dq, bool *in_sq)
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
	int		fchange;
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
		quote_conditiions(*str, &in_dq, &in_sq);
		if (is_escaped(str))
			str++;
		str++;
	}
	printf("wordcount = %d\n", wc);
	return (wc);
}
