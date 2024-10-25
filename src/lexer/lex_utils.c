/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:40:15 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/25 12:13:53 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

void	fill_lexem(t_lexem *lexem, char *str, t_token token, bool meta)
{
	lexem->value = ft_strdup(str);
	lexem->token = token;
	lexem->is_meta = meta;
}

void	free_lex(t_lexer *lex)
{
	int		idx;
	t_lexem	lexem;
	char	**words;

	idx = 0;
	lexem = lex->lexems[idx];
	while (lexem.value)
	{
		free(lexem.value);
		lexem = lex->lexems[++idx];
	}
	words = lex->words;
	idx = 0;
	while (words[idx])
		free(words[idx++]);
}

static inline int	display_lexem_aux(t_token token)
{
	if (token == PIPE)
		return(printf("[%sPIPE%s]\n", GREEN_TXT, END_TXT));
	else if (token == AND)
		return(printf("[%sAND%s]\n", GREEN_TXT, END_TXT));
	else if (token == OR)
		return(printf("[%sOR%s]\n", GREEN_TXT, END_TXT));
	else if (token == REDIR_APPEND)
		return(printf("[%sREDIR_APPEND%s]\n", GREEN_TXT, END_TXT));
	else if (token == REDIR_OUT)
		return(printf("[%sREDIR_OUT%s]\n", GREEN_TXT, END_TXT));
	else if (token == REDIR_IN)
		return(printf("[%sREDIR_IN%s]\n", GREEN_TXT, END_TXT));
	else if (token == HEREDOC)
		return(printf("[%sHEREDOC%s]\n", GREEN_TXT, END_TXT));
	else if (token == HERESTRING)
		return(printf("[%sHERESTRING%s]\n", GREEN_TXT, END_TXT));
	else if (token == CMD)
		return(printf("[%sCMD%s]\n", GREEN_TXT, END_TXT));
	else if (token == WORD)
		return(printf("[%sWORD%s]\n", GREEN_TXT, END_TXT));
	else if (token == F_NAME)
		return(printf("[%sF_NAME%s]\n", GREEN_TXT, END_TXT));
	else if (token == LIMITER)
		return(printf("[%sLIMITER%s]\n", GREEN_TXT, END_TXT));
	return(printf("[%sERROR%s]\n", RED_TXT, END_TXT));
}

void	print_lexems(t_lexer *lex)
{
	int	i;

	printf("\n%s===Lexing Status===%s\n===\n", YELLOW_TXT, END_TXT);
	i = -1;
	while (lex->words[++i + 1])
	{
		printf("===[%s%s%s] ----> ", YELLOW_TXT, lex->words[i], END_TXT);
		display_lexem_aux(lex->lexems[i].token);
	}
	printf("===[%s%s%s] ----> ", YELLOW_TXT, lex->words[i], END_TXT);
	display_lexem_aux(lex->lexems[i].token);
	printf("===\n%s===Lexing Status===%s\n", YELLOW_TXT, END_TXT);
}
