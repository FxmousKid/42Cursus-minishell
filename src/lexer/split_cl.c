/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:21:40 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/25 00:04:58 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

bool	is_escaped(char *str);
void	quote_conditions(char c, bool *in_dq, bool *in_sq);


static inline void	get_len_word(char *str, int *len)
{
	int		len_w;
	bool	in_sq;
	bool	in_dq;

	in_dq = false;
	in_sq = false;
	len_w = 0;
	while (str[len_w])
	{
		quote_conditions(str[len_w], &in_dq, &in_sq);
		if (is_escaped(str + len_w))
		{
			len_w += 2;
			continue;
		}
		if (!in_sq && !in_dq && str[len_w] == ' ')
			break;
		if (is_meta_char(str + len_w) && !len_w && !in_dq && !in_sq)
		{
			len_w += is_meta_char(str + len_w);
			break;
		}
		else if (is_meta_char(str + len_w) && !in_dq && !in_sq)
			break;
		len_w++;
	}
	*len = len_w;
}

bool	split_mod(char *str, char **words)
{
	int	len_word;
	int	len_max;

	len_word = 0;
	len_max = ft_strlen(str);
	while (len_max > 0)
	{
		get_len_word(str, &len_word);
		if (len_word == 0)
		{
			str++;
			len_max--;
			continue;
		}
		*words = (char *) ft_calloc(len_word + 1, sizeof(char));
		if (!*words)
			return (debug(DBG("Failed to allocate memory")), false);
		ft_strlcpy(*words++, str, len_word + 1);
		str += len_word;
		len_max -= len_word;
	}
	return (true);
}

void	clean_space_tabs(char *str)
{
	int	idx;
	int	rm_flag;

	rm_flag = 0;
	idx = -1;
	while (str[++idx])
	{
		if (is_occ_aux(str[idx], " \t") && rm_flag)
		{
			ft_memmove(str + idx - 1, str + idx, ft_strlen(str + idx) + 1);
			idx--;
		}
		rm_flag = is_occ_aux(str[idx], " \t");
	}
	if (is_occ_aux(str[0], " \t"))
		ft_memmove(str, str + 1, ft_strlen(str));
	if (is_occ_aux(str[ft_strlen(str) - 1], " \t"))
		str[ft_strlen(str) - 1] = '\0';
}

bool	split_cl(char *str, t_lexer *lex)
{
	// clean_space_tabs(str);
	// printf("cleaned str: [%s]\n", str);
	if (!split_mod(str, lex->words))
		return (debug(DBG("Failed to split_mod()")), false);
	return (true);
}
