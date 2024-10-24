/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:00:58 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/25 00:05:15 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	parse_first_word(char *word, t_lexem *lexem)
{
	if (word[0] == '$')
		return (fill_lexem(lexem, word, ENV_VAR, false));	
	// to add builtin-recognition
	fill_lexem(lexem, word, CMD, false);
}

void	lex_general(t_lexer *lex)
{
	int	lex_idx;

	lex_idx = 0;
	parse_first_word(lex->words[0], &lex->lexems[0]);
	while (lex->words[++lex_idx])
	{
		if (lex_if_meta_chars(&lex->lexems[lex_idx], lex->words[lex_idx]))
			continue;
		fill_lexem(&lex->lexems[lex_idx], lex->words[lex_idx], WORD, false);
	}
}

bool	lexer(t_lexer *lex, char *str)
{
	if (!*str)
		return (debug(DBG("Empty string")), false);
	if (!split_cl(str, lex))
		return (debug(DBG("Failed to split_cl()")), false);
	print_split(lex->words);
	lex_general(lex);
	return (true);
}
