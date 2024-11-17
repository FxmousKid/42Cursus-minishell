/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:02:06 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/17 18:58:16 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "macros.h"
#include "minishell.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

char	*readline_fancy_ps_two(t_lexer *lex, char *ps_two, bool to_read);

char	*trim_limiter_quotes(char *limiter, bool *to_free)
{
	char	*trimmed_lim;

	if (limiter[0] != '\'' && limiter[0] != '"')
		return (limiter);
	trimmed_lim = ft_calloc(sizeof(char), ft_strlen(limiter) - 1);
	if (!trimmed_lim)
		return (NULL);
	*to_free = true;
	limiter++;
	ft_strlcpy(trimmed_lim, limiter, ft_strlen(limiter));
	return (trimmed_lim);
}

bool	check_if_heredocs_done(t_lexer *lex, char **hdocs, char **hdocs_dq)
{
	size_t	len_hdocs;
	size_t	len_hdocs_dq;
	
	len_hdocs = strptr_len(hdocs, MAX_HEREDOCS);
	len_hdocs_dq = strptr_len(hdocs_dq, MAX_HEREDOCS);

	return (!has_n_token(lex, HEREDOC, len_hdocs_dq + len_hdocs));
}


void	read_heredoc(char *limiter, char *prompt, char **heredoc)
{
	char	hd_content[4096];
	char	*line;
	char	*trim_lim;
	bool	to_free;

	ft_bzero(hd_content, sizeof(char) * 4096);
	line = readline(prompt);
	to_free = false;
	trim_lim = trim_limiter_quotes(limiter, &to_free);
	if (strcmp(line, trim_lim))
	{
		ft_strlcat(hd_content, line, 4096);
		free(line);
		line = readline(prompt);
	}
	while (strcmp_ex(line, trim_lim))
	{
		ft_strlcat(hd_content, "\n", 4096);
		ft_strlcat(hd_content, line, 4096);
		line = readline(prompt);
	}
	if (to_free)
		free(trim_lim);
	*heredoc = ft_strdup(hd_content);
}

void	start_correct_heredoc(t_lexer *lex, int *idx, char **hd, char **hd1)
{
	size_t	len_hdocs;
	size_t	len_hdocs_dq;
	
	len_hdocs = strptr_len(hd, MAX_HEREDOCS);
	len_hdocs_dq = strptr_len(hd1, MAX_HEREDOCS);
	if (len_hdocs_dq + len_hdocs == 0)
		return ;
	while (len_hdocs + len_hdocs_dq > 0)
	{
		if (lex->lexems[*idx].token == HEREDOC)
		{
			if (lex->lexems[*idx + 1].token == Q_LIMITER)
				len_hdocs_dq--;
			else
				len_hdocs--;
		}
		(*idx)++;
	}
}

bool	prompt_for_heredocs(t_lexer *lex, char **heredocs, char **heredocs_dq)
{
	char	*prompt;
	int		idx;

	if (!check_if_heredocs_done(lex, heredocs, heredocs_dq))
		return (false);
	idx = 0;
	start_correct_heredoc(lex, &idx, heredocs, heredocs_dq);
	while (has_token(lex->lexems + ++idx, HEREDOC))
	{
		while (lex->lexems[idx].token != HEREDOC)
			idx++;
		prompt = readline_fancy_ps_two(lex, PS2_HDOC, false);
		if (!prompt)
			return (debug(DBG("heredoc prompt is null")), false);
		if (lex->lexems[idx + 1].token == Q_LIMITER)
			read_heredoc(lex->lexems[idx + 1].value, prompt, \
				heredocs_dq + strptr_len(heredocs_dq, MAX_HEREDOCS));
		else
			read_heredoc(lex->lexems[idx + 1].value, prompt, \
				heredocs + strptr_len(heredocs, MAX_HEREDOCS));
	}
	return (free(prompt), true);
}
