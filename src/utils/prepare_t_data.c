/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_t_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:22:50 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/13 11:45:32 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data, char *readline_input)
{
	free(readline_input);
	free_lex(&data->lex);	
}

void	init_t_data(t_data *data)
{
	data->env = NULL;
	ft_bzero(&data->lex, sizeof(t_lexer));
}

void	free_and_init_data(t_data *data, char *readline_input)
{
	free_data(data,	readline_input);
	init_t_data(data);
}
