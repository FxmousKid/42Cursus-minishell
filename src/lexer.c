/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:25:52 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/17 17:01:09 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <string.h>

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
		{
			if (lex->lexems[lex_idx].value[0] == '"')
				lex->lexems[lex_idx].token = Q_LIMITER;
			else
				lex->lexems[lex_idx].token = LIMITER;
		}
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

void	lex_words_into_sq_dq(t_lexer *lex)
{
	size_t	idx;

	idx = 0;
	while (idx < lex->lexem_count)
	{
		if (lex->lexems[idx].token == WORD)
		{
			if (lex->lexems[idx].value[0] == '"')
				lex->lexems[idx].token = DQ_WORD;
			else if (lex->lexems[idx].value[0] == '\'')
				lex->lexems[idx].token = SQ_WORD;
		}
		idx++;
	}
}

bool	lexer(t_lexer *lex, char *input)
{
 	if (!*input)
		return (debug(DBG("Null string")), false);
	ft_strlcpy(lex->input, input, sizeof(lex->input));
	if (!split_cl(lex))
		return (debug(DBG("Failed to split_cl()")), false);
	lex_general(lex);
	lex_files_and_heredoc(lex);
	lex_commands_after_pipe(lex);
	lex_words_into_sq_dq(lex);
	return (true);
}
