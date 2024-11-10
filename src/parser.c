/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:36:25 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/10 19:56:51 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* the Goal here is to analyze syntax.
 * 1) Check for definitive syntaxically unfixable tokens : "echo |||"
 *	  cash : parse error near `META_CHARACTER' 
 * 2) Read heredocs 
 * 3) Fill command structures
 * 
 * */


bool	parser(t_data *data, t_lexer *lex)
{
	(void)	data;
	char	*heredocs_content[MAX_HEREDOCS];

	if (!search_parse_error(lex))
		return (debug(DBG("Failed to search_parse_error()")), false);	
	if (!read_heredocs(lex, heredocs_content))
		return (debug(DBG("Failed to read_heredocs()")), false);
	return (true);
}
