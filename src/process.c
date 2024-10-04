/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:38:55 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/04 23:06:23 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_process(t_data *data, t_ast *pro)
{
    if (pro->token == CMD)
        return (cmd_process(data, pro));
	if (pro->token == PIPE)
        return (pipe_process(data, pro));
	if (pro->token == REDIR_IN)
        return (redirin_process(data, pro));
	if (pro->token == REDIR_OUT)
        return (redirout_process(data, pro));
	if (pro->token == REDIR_APPEND)
        return (redirin_append_process(data, pro));
	if (pro->token == HEREDOC)
        return (heredoc_process(data, pro));
	if (pro->token == EQUAL)
        return (equal_process(data, pro));
	if (pro->token == OR)
        return (or_process(data, pro));
	if (pro->token == AND)
        return (and_process(data, pro));
    return (0);
}
