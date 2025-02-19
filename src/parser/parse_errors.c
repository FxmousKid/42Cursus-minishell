/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:43:31 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 23:31:35 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parse_error(char *unexpected_token)
{
	printf(PARSE_ERROR);
	printf("`%s'\n", unexpected_token);
}

bool	verify_meta_char_parse(t_lexer *lex, int idx, char **unexpected_token)
{
	if (idx == 0 && lex->lexems[idx].token != REDIR_IN \
		&& lex->lexems[idx].token != HEREDOC \
		&& lex->lexems[idx].token != HERESTRING \
		&& lex->lexems[idx].token != REDIR_OUT \
		&& lex->lexems[idx].token != REDIR_APPEND)
		return (debug(DBG("Forbidden meta char found")), false);
	else if (idx == 0)
		return (true);
	if (lex->lexems[idx + 1].is_meta)
	{
		*unexpected_token = lex->lexems[idx + 1].value;
		return (debug(DBG("Two meta chars in a row")), false);
	}
	return ((void) unexpected_token, true);
}

bool	verify_pipe_parse(t_lexer *lex, int idx, char **unexpected_token)
{
	if (lex->lexems[idx].token != PIPE)
		return (true);
	if (idx == 0)
	{
		*unexpected_token = lex->lexems[idx].value;
		return (debug(DBG("Pipe not allowed in beginning")), false);
	}
	return ((void) unexpected_token, true);
}

bool	verifiy_trailing_meta_char(t_lexer *lex, char **unexpected_token)
{
	t_lexem	lexem;

	lexem = lex->lexems[lex->lexem_count - 1];
	if (lexem.is_meta)
	{
		if (lexem.token == PIPE)
			return (true);
		*unexpected_token = lexem.value;
		return (false);
	}
	return (true);
}

/* parse_status = cond1 && cond2 && ... because it will check for all 
 * parse error checks until it finds one */

bool	search_parse_error(t_lexer *lex)
{
	int		i;
	bool	parse_status;
	char	*unexpected_tok;

	i = -1;
	unexpected_tok = NULL;
	parse_status = verifiy_trailing_meta_char(lex, &unexpected_tok);
	while ((size_t)++i < lex->lexem_count)
	{
		if (!parse_status)
			return (print_parse_error(unexpected_tok), false);
		if (lex->lexems[i].is_meta)
		{
			parse_status = verify_meta_char_parse(lex, i, &unexpected_tok);
			parse_status &= verify_pipe_parse(lex, i, &unexpected_tok);
		}
	}
	return (parse_status);
}
