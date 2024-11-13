/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_for_partial_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:07:09 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/13 11:38:55 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline_fancy_ps_two(t_lexer *lex, char *ps_two);

bool	prompt_for_partial_pipe(t_lexer *lex)
{
	char	*line;

	if (lex->lexems[lex->lexem_count - 1].token == PIPE)
	{
		line = readline_fancy_ps_two(lex, PS2);	 
		ft_strlcat(lex->input, line, PATH_MAX);
		free(line);
		return (true);
	}
	return (false);
}
