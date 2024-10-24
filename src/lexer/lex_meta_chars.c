/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_meta_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:42:28 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/24 21:00:57 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include <stdbool.h>

int is_meta_char(char *str)
{
	if (!ft_strncmp("&&", str, 2)) 
		return (2);
	else if (!ft_strncmp("||", str, 2))
		return (2);
	else if (!ft_strncmp(">>", str, 2))
		return (2);
	else if (!ft_strncmp("<<", str, 2))
		return (2);
	else if (!ft_strncmp("<<<", str, 3))
		return (3);
	else if (!ft_strncmp(">", str, 1))
		return (1);
	else if (!ft_strncmp("<", str, 1))
		return (1);
	else if (!ft_strncmp("|", str, 1))
		return (1);
	return (0);


}

static inline bool	is_meta_char_only(char *str)
{
	bool	is_meta;

	is_meta = ft_strlen(str) == 1;
	is_meta &= is_occ_aux(*str, META_CHARACTERS);
	return (is_meta);
}

bool	lex_if_meta_chars(t_lexem *lexem, char *str)
{
	if (!is_meta_char_only(str))
		return (false);
	if (!ft_strncmp("&&", str, 2) && ft_strlen(str) == 2)
		fill_lexem(lexem, "&&", AND, true);
	else if (!ft_strncmp("||", str, 2) && ft_strlen(str) == 2)
		fill_lexem(lexem, "||", OR, true);
	else if (!ft_strncmp(">>", str, 2) && ft_strlen(str) == 2)
		fill_lexem(lexem, ">>", REDIR_APPEND, true);
	else if (!ft_strncmp("<<", str, 2) && ft_strlen(str) == 2)
		fill_lexem(lexem, "<<", HEREDOC, true);
	else if (!ft_strncmp("<<<", str, 3) && ft_strlen(str) == 3)
		fill_lexem(lexem, "<<<", HERESTRING, true);
	else if (!ft_strncmp(">", str, 1) && ft_strlen(str) == 1)
		fill_lexem(lexem, ">", REDIR_OUT, true);
	else if (!ft_strncmp("<", str, 1) && ft_strlen(str) == 1)
		fill_lexem(lexem, "<", REDIR_IN, true);
	else if (!ft_strncmp("|", str, 1) && ft_strlen(str) == 1)
		fill_lexem(lexem, "|", PIPE, true);
	return (true);
}
