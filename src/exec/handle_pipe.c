/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:48:54 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 15:01:31 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "exec.h"
#include "minishell.h"

int	handle_pipe(t_ast *node, t_data *data, t_exec_data *e_data)
{
	(void) e_data;
	(void) data;
	(void) node;
	
	if (pipe(e_data->pipefd) < 0)
		return (debug(DBG("Failed to pipe()")), false);


	return (1);
}
