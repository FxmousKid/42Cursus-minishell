/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_for_partial_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:38:59 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/11 02:45:41 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

extern bool	is_escaped(char *str);
extern void	quote_conditions(char c, bool *in_dq, bool *in_sq);

void	fill_quotes_states(char *str, bool *dq_sq)
{
	int	idx;

	dq_sq[0] = false;
	dq_sq[1] = false;
	idx = -1; 
	while (str[++idx])
	{
		quote_conditions(str[idx], dq_sq, dq_sq + 1);
		if (is_escaped(str + idx))
		{
			idx += 2;
			continue;
		}
	}
}

char	*readline_fancy_ps_two(t_lexer *lex, char *ps_two)
{
	int		pipe_count;
	int		idx;
	char	ps_two_fancy[128];

	ft_bzero(ps_two_fancy, 128);
	idx = -1;
	pipe_count = 0;
	while (++idx < (int) lex->lexem_count)
	{
		if (lex->lexems[idx].token == PIPE)
			pipe_count++;
	}
	while (--pipe_count >= 0)
		ft_strlcat(ps_two_fancy, "pipe ", 128);
	if (ps_two_fancy[0] && ps_two_fancy[ft_strlen(ps_two_fancy) - 1] == ' ' \
		&& !strcmp_ex(ps_two, PS2))
		ps_two_fancy[ft_strlen(ps_two_fancy) - 1] = '\0';
	ft_strlcat(ps_two_fancy, ps_two, 128);
	return (readline(ps_two_fancy));
}

void	p_fill_quote(char *line, char *partial_fill, bool dq_sq[2], t_lexer *lex)
{
	strlcat(partial_fill, "\n", 4096);
	if (dq_sq[0])
	{
		line = readline_fancy_ps_two(lex, PS2_DQ);
		strlcat(partial_fill, line, 4096);
		while (!is_occ_aux('"', line))
		{
			strlcat(partial_fill, "\n", 4096);
			free(line);
			line = readline_fancy_ps_two(lex, PS2_DQ);
			strlcat(partial_fill, line, 4096);
		}
	}
	else if (dq_sq[1])
	{
		line = readline_fancy_ps_two(lex, PS2_SQ);
		strlcat(partial_fill, line, 4096);
		while (!is_occ_aux('\'', line))
		{
			strlcat(partial_fill, "\n", 4096);
			free(line);
			line = readline_fancy_ps_two(lex, PS2_SQ);
			strlcat(partial_fill, line, 4096);
		}
	}
	free(line);
}

bool	prompt_for_partial_sq_dq(t_lexer *lex)
{
	bool	dq_sq[2];
	char	partial_fill[4096];
	char	*line;
	char	*tmp;

	ft_bzero(partial_fill, 4096);
	fill_quotes_states(lex->input, dq_sq);
	line = NULL;
	p_fill_quote(line, partial_fill, dq_sq, lex);
	if (!dq_sq[0] && !dq_sq[1])
		return (false);
	if (lex->input_joined)
	{
		tmp = ft_strdup(lex->input);
		free(lex->input);
		lex->input = ft_strjoin(tmp, partial_fill);;
		free(tmp);
	}
	else
		lex->input = ft_strjoin(lex->input, partial_fill);
	lex->input_joined = true;
	return (true);
}
