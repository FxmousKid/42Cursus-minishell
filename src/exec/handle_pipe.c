/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:48:54 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/13 18:10:24 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"

void	check_to_open_pipe(t_ast *node, t_exec_data *e_data)
{
	if (!is_tok_dual_cmd_type(node->token))
		return ;
	if (pipe(e_data->pipefd) < 0)
	{
		e_data->pipefd[0] = -1;
	}
}
