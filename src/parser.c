/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:36:25 by inazaria          #+#    #+#             */
/*   Updated: 2024/12/31 00:41:05 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minishell.h"
#include "utils.h"

static void	handle_partial_prompt(t_data *data, t_lexer *lex)
{
	char	tmp[PATH_MAX];

	ft_bzero(tmp, sizeof(tmp));
	ft_strlcpy(tmp, lex->input, PATH_MAX);
	free_lex(lex);
	ft_bzero(lex, sizeof(t_lexer));
	lexer(lex, tmp);
	if (!search_parse_error(lex))
	{
		data->exit_code = 2;
		debug(DBG("Failed to search_parse_error()"));	
	}
}

bool	prompt_for_partials_and_heredoc(t_data *data, t_lexer *lex)
{
	if (prompt_for_partial_sq_dq(lex))
	{
		handle_partial_prompt(data, lex);
		return (prompt_for_partials_and_heredoc(data, lex));
	}
	prompt_for_heredocs(lex, data->heredocs, data->heredocs_dq);
	if (prompt_for_partial_pipe(lex))
	{
		handle_partial_prompt(data, lex);
		return (prompt_for_partials_and_heredoc(data, lex));
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

bool	parser(t_data *data, t_lexer *lex)
{
	if (!search_parse_error(lex))
	{
		data->exit_code = 2;
		return (debug(DBG("Failed to search_parse_error()")), false);	
	}
	if (!prompt_for_partials_and_heredoc(data, lex))
		return (debug(DBG("Failed to prompt_for_partials()")), false);

	if (!init_and_fill_ast(data))
		return (debug(DBG("Failed to init_ast()")), false);
	

	printf("\n");
	print_split(data->heredocs, "data->heredocs");
	print_split(data->heredocs_dq, "data->heredocs_dq");

	return (true);
}
