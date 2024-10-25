/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:00:58 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/25 11:30:05 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdbool.h>


/* We start at the second lexem because i do backwards check */

bool	lex_files_and_heredoc(t_lexer *lex)
{
	int	lex_idx;

	lex_idx = 0;
	while (lex->words[++lex_idx])
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
	return (true);
}

bool	lex_general(t_lexer *lex)
{
	int	lex_idx;

	// to add builtin-recognition
	if (*lex->words[0] == '$')
		fill_lexem(&lex->lexems[0], lex->words[0], ENV_VAR, false);	
	else
		fill_lexem(&lex->lexems[0], lex->words[0], CMD, false);	
	lex_idx = 0;
	while (lex->words[++lex_idx])
	{
		if (lex_if_meta_chars(&lex->lexems[lex_idx], lex->words[lex_idx]))
			continue;
		fill_lexem(&lex->lexems[lex_idx], lex->words[lex_idx], WORD, false);
	}
	return (true);
}

bool	lexer(t_lexer *lex, char *str)
{
	if (!*str)
		return (debug(DBG("Empty string")), false);
	if (!split_cl(str, lex))
		return (debug(DBG("Failed to split_cl()")), false);
	print_split(lex->words);

	if (!lex_general(lex))
		return (debug(DBG("Failed to lex_general()")), false);

	if (!lex_files_and_heredoc(lex))
		return (debug(DBG("Failed to lex_files_and_heredoc()")), false);
	
	print_lexems(lex);
	return (true);
}

