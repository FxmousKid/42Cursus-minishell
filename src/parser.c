/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:36:25 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/13 11:38:45 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minishell.h"

static void	handle_partial_prompt(t_lexer *lex)
{
	char	tmp[PATH_MAX];

	ft_bzero(tmp, sizeof(tmp));
	ft_strlcpy(tmp, lex->input, PATH_MAX);
	
	int c = lex->lexem_count;
	lex->lexem_count = c + 1;
	print_lexems(lex);
	lex->lexem_count = c;

	free_lex(lex);
	ft_bzero(lex, sizeof(t_lexer));

	lexer(lex, tmp);
}

static bool	prompt_for_partials(t_data *data, t_lexer *lex)
{
	if (prompt_for_partial_sq_dq(lex) ^ prompt_for_partial_pipe(lex))
	{
		handle_partial_prompt(lex);
		return (parser(data, lex));
	}
	return (true);
}

/* the Goal here is to analyze syntax.
 * 1) Check for definitive syntaxically unfixable tokens : "echo |||"
 *	  cash : parse error near `META_CHARACTER' 
 * 2) Fill partially filled single/double quotes, and pipes
 *	  "echo |", echo "aaa
 * 3) Read heredocs
 * 4) expand variables
 * 5) Fill command structures
 *
 * on failure, return the exit code of the appropriate failure type
 * e.g. 2 for syntax error.
 * */

int	parser(t_data *data, t_lexer *lex)
{
	(void)	data;
	char	*heredocs_content[MAX_HEREDOCS];

	ft_bzero(heredocs_content, sizeof(heredocs_content));
	if (!search_parse_error(lex))
		return (debug(DBG("Failed to search_parse_error()")), 2);	
	if (!prompt_for_partials(data, lex))
		return (debug(DBG("Failed to prompt_for_partials()")), false);
	if (!read_and_expand_heredocs(lex, heredocs_content))
		return (debug(DBG("Failed to read_heredocs()")), false);
	return (true);
}
