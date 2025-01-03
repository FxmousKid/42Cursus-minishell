/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_t_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:22:50 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/03 01:36:32 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* We use this instead of free_split() because we only want to free 
 * the content of the heredocs, not the heredocs itself since it's on the stack */
void	free_heredocs(t_data *data)
{
	int	idx;

	idx = 0;
	while (data->heredocs[idx])
		free(data->heredocs[idx++]);
	idx = 0;
	while (data->heredocs_dq[idx])
		free(data->heredocs_dq[idx++]);
}

void	free_data(t_data *data, char *readline_input)
{
	free(readline_input);
	free_lex(&data->lex);
	free_heredocs(data);
	free_ast(data->ast);
}


void	free_data_w_env(t_data *data, char *readline_input)
{
	free_data(data, readline_input);
	free_env(data->env);
}


void	init_t_data(t_data *data)
{
	data->env = NULL;
	ft_bzero(&data->lex, sizeof(t_lexer));
	ft_bzero(data->heredocs, sizeof(data->heredocs));
	ft_bzero(data->heredocs_dq, sizeof(data->heredocs_dq));
	ft_bzero(&data->ast, sizeof(t_ast));
}

void	free_and_init_data(t_data *data, char *readline_input)
{
	free_data(data,	readline_input);
	init_t_data(data);
}

