/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:31:41 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:31:45 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_lexem(t_lexem *lexem, char *str, t_token token, bool meta)
{
	lexem->value = ft_strdup(str);
	lexem->token = token;
	lexem->is_meta = meta;
}

void	free_lex(t_lexer *lex)
{
	size_t	idx;
	char	**words;
	t_lexem	*lexems;

	if (!lex)
		return ;
	lexems = lex->lexems;
	idx = 0;
	while (idx < lex->lexem_count)
		free(lexems[idx++].value);
	lex->lexem_count = 0;
	words = lex->words;
	idx = 0;
	while (words[idx])
	{
		free(words[idx]);
		words[idx++] = NULL;
	}
}

static inline int	display_lexem_aux_2(t_token token)
{
	if (token == HERESTRING)
		return (printf("[%sHERESTRING%s]\n", GREEN_TXT, END_TXT));
	else if (token == CMD)
		return (printf("[%sCMD%s]\n", GREEN_TXT, END_TXT));
	else if (token == WORD)
		return (printf("[%sWORD%s]\n", GREEN_TXT, END_TXT));
	else if (token == F_NAME)
		return (printf("[%sF_NAME%s]\n", GREEN_TXT, END_TXT));
	else if (token == LIMITER)
		return (printf("[%sLIMITER%s]\n", GREEN_TXT, END_TXT));
	else if (token == ENV_VAR)
		return (printf("[%sENV_VAR%s]\n", GREEN_TXT, END_TXT));
	else if (token == SQ_WORD)
		return (printf("[%sSQ_WORD%s]\n", GREEN_TXT, END_TXT));
	else if (token == DQ_WORD)
		return (printf("[%sDQ_WORD%s]\n", GREEN_TXT, END_TXT));
	return (printf("[%sERROR%s]\n", RED_TXT, END_TXT));
}

static inline int	display_lexem_aux(t_token token)
{
	if (token == PIPE)
		return (printf("[%sPIPE%s]\n", GREEN_TXT, END_TXT));
	else if (token == AND)
		return (printf("[%sAND%s]\n", GREEN_TXT, END_TXT));
	else if (token == OR)
		return (printf("[%sOR%s]\n", GREEN_TXT, END_TXT));
	else if (token == REDIR_APPEND)
		return (printf("[%sREDIR_APPEND%s]\n", GREEN_TXT, END_TXT));
	else if (token == REDIR_OUT)
		return (printf("[%sREDIR_OUT%s]\n", GREEN_TXT, END_TXT));
	else if (token == REDIR_IN)
		return (printf("[%sREDIR_IN%s]\n", GREEN_TXT, END_TXT));
	else if (token == HEREDOC)
		return (printf("[%sHEREDOC%s]\n", GREEN_TXT, END_TXT));
	else if (token == Q_LIMITER)
		return (printf("[%sQ_LIMITER%s]\n", GREEN_TXT, END_TXT));
	return (display_lexem_aux_2(token));
}

void	print_lexems(t_lexer *lex, t_data *data)
{
	int	i;

	printf("\n%s===Lexing Status %s", YELLOW_TXT, END_TXT);
	printf("[%zu]%s===%s\n", lex->lexem_count, YELLOW_TXT, END_TXT);
	printf("%sinput%s : [%s%s%s]\n", GREEN_TXT, END_TXT, YELLOW_TXT, \
		lex->input, END_TXT);
	print_split(lex->words, "Words");
	i = -1;
	while (++i < ((int) lex->lexem_count) - 1)
	{
		printf("===[%s%s", YELLOW_TXT, lex->lexems[i].value);
		printf("%s] ----> ", END_TXT);
		display_lexem_aux(lex->lexems[i].token);
	}
	if (lex->lexem_count)
	{
		printf("===[%s%s%s] ", YELLOW_TXT, lex->lexems[i].value, END_TXT);
		printf("----> ");
		display_lexem_aux(lex->lexems[i].token);
	}
	printf("%s===Lexing Status===%s\n\n", YELLOW_TXT, END_TXT);
	print_split(data->heredocs, "data->heredocs");
	print_split(data->heredocs_dq, "data->heredocs_dq");
}
