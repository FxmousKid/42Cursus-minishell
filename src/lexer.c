/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:25:52 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/28 16:01:53 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <string.h>

static inline void	set_lexems_count(t_lexer *lex)
{
	int	lexem_count;

	lexem_count = 0;
	while (lex->words[lexem_count])
		lexem_count++;
	lex->lexem_count = lexem_count;
}

/* We start at the 3rd lexem :
   x | y
       ^ we start here and do backwards check */

void	lex_commands_after_pipe(t_lexer *lex)
{
	size_t	lex_idx;

	lex_idx = 1;
	while (++lex_idx < lex->lexem_count)
	{
		if (lex->lexems[lex_idx - 1].token == PIPE)
			lex->lexems[lex_idx].token = CMD;
	}
}

/* We start at the second lexem because i do backwards check */
void	lex_files_and_heredoc(t_lexer *lex)
{
	size_t	lex_idx;

	lex_idx = 0;
	while (++lex_idx < lex->lexem_count)
	{
		if (lex->lexems[lex_idx - 1].token == REDIR_IN)
			lex->lexems[lex_idx].token = F_NAME;
		else if (lex->lexems[lex_idx - 1].token == REDIR_OUT)
			lex->lexems[lex_idx].token = F_NAME;
		else if (lex->lexems[lex_idx - 1].token == REDIR_APPEND)
			lex->lexems[lex_idx].token = F_NAME;
		else if (lex->lexems[lex_idx - 1].token == HEREDOC)
			lex->lexems[lex_idx].token = LIMITER;
	}
}

void	lex_general(t_lexer *lex)
{
	size_t	lex_idx;

	if (*lex->words[0] == '$')
		fill_lexem(&lex->lexems[0], lex->words[0], ENV_VAR, false);
	else if (!lex_if_meta_chars(&lex->lexems[0], lex->words[0]))
		fill_lexem(&lex->lexems[0], lex->words[0], CMD, false);
	lex_idx = 0;
	while (++lex_idx < lex->lexem_count)
	{
		if (lex_if_meta_chars(&lex->lexems[lex_idx], lex->words[lex_idx]))
			continue ;
		if (*lex->words[lex_idx] == '$')
			fill_lexem(&lex->lexems[lex_idx], lex->words[lex_idx], ENV_VAR, false);
		else
			fill_lexem(&lex->lexems[lex_idx], lex->words[lex_idx], WORD, false);
	}
}

bool	lexer(t_lexer *lex, char *str)
{
	if (!*str)
		return (debug(DBG("Empty string")), false);
	if (!split_cl(str, lex))
		return (debug(DBG("Failed to split_cl()")), false);
	set_lexems_count(lex);
	lex_general(lex);
	lex_files_and_heredoc(lex);
	lex_commands_after_pipe(lex);
	print_split(lex->words);
	return (true);
}
