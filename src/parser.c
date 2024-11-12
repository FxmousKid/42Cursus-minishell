/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:36:25 by inazaria          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/11/11 15:45:20 by inazaria         ###   ########.fr       */
=======
/*   Updated: 2024/11/12 17:38:19 by inazaria         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* the Goal here is to analyze syntax.
 * 1) Check for definitive syntaxically unfixable tokens : "echo |||"
 *	  cash : parse error near `META_CHARACTER' 
 * 2) Fill partially filled single/double quotes, and pipes
 * 3) Read heredocs 
 * 4) Fill command structures
 * 
 * */

static void	handle_partial_quote_or_pipe(t_lexer *lex)
{
	char	tmp[4096];

	ft_bzero(tmp, 4096);
	ft_strlcpy(tmp, lex->input, 4096);
	free_lex(lex);
	lexer(lex, ft_strdup(tmp));
}

bool	prompt_for_partials(t_data *data, t_lexer *lex)
{
	if (prompt_for_partial_sq_dq(lex))
	{
		handle_partial_quote_or_pipe(lex);
		return (parser(data, lex));
	}
	if (prompt_for_partial_pipe(lex))
	{
		handle_partial_quote_or_pipe(lex);
		return (parser(data, lex));
	}
	return (true);
}


bool	parser(t_data *data, t_lexer *lex)
{
	(void)	data;
	char	*heredocs_content[MAX_HEREDOCS];
	char	tmp[4096];

	ft_bzero(heredocs_content, sizeof(heredocs_content));
	ft_bzero(tmp, sizeof(tmp));
	if (!search_parse_error(lex))
		return (debug(DBG("Failed to search_parse_error()")), false);	
	if (!prompt_for_partials(data, lex))
		return (debug(DBG("Failed to prompt_for_partials()")), false);
	if (!read_and_expand_heredocs(lex, heredocs_content))
		return (debug(DBG("Failed to read_heredocs()")), false);


	print_split(data->env->paths);

	return (true);
}
