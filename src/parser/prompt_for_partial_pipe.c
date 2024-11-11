/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_for_partial_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:07:09 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/11 02:31:41 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline_fancy_ps_two(t_lexer *lex, char *ps_two);

bool	prompt_for_partial_pipe(t_lexer *lex)
{
	char	*line;
	char	*tmp;

	if (lex->lexems[lex->lexem_count - 1].token == PIPE)
	{
		line = readline_fancy_ps_two(lex, PS2);	 
		if (lex->input_joined)
		{
			tmp = ft_strdup(lex->input);
			free(lex->input);
			lex->input = ft_strjoin(tmp, line);
			free(tmp);
		}
		else
			lex->input = ft_strjoin(lex->input, line);
		free(line);
		lex->input_joined = true;
		return (true);
	}
	return (false);
}
