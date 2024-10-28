/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:43:31 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/28 14:33:05 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parse_error(t_lexem lexem)
{
	printf("%s: parse error near `%s'\n", SH_NAME, lexem.value);
}

bool	verify_meta_char_parse(t_lexer *lex, int idx)
{
	if (idx == 0 && lex->lexems[idx].token != REDIR_IN)
		return (debug(DBG("Forbidden meta char found")), false);
	else if (idx == 0)
		return (true);


	return (true);
}

bool	verify_pipe_parse(t_lexer *lex, int idx)
{
	if (lex->lexems[idx].token != PIPE)
		return (true);
	if (idx == 0)
		return (debug(DBG("Pipe not allowed in beginning")), false);
	return (true); 
}

bool	search_parse_error(t_lexer *lex)
{
	int		i;
	bool	parse_status;

	i = -1;
	parse_status = true;
	while ((size_t) ++i < lex->lexem_count)
	{
		printf("Lexem: %d\n", lex->lexems[i].is_meta);
		if (lex->lexems[i].is_meta)
		{
			parse_status &= verify_meta_char_parse(lex, i);
			parse_status &= verify_pipe_parse(lex, i);
			// parse_status &= 

		}
		if (!parse_status)
			print_parse_error(lex->lexems[i]);
		
	}
	return (parse_status);
}
