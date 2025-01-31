/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:09:19 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 17:38:45 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	write_dup_heredoc_stdin(t_ast *cmd_node, t_exec_data *e_data)
{
	char	*hdoc;

	if (!cmd_node->ast_cmd.is_hdoc)
		return true;
	hdoc = cmd_node->ast_cmd.cmd_args[1];
	if (pipe(e_data->pipefd) < 0)
		return (debug(DBG("Failed to pipe()")), false);
	if (write(e_data->pipefd[1], hdoc, ft_strlen(hdoc)) < 0)
		return (debug(DBG("Failed to write()")), false);
	if (close(e_data->pipefd[1]) < 0)
		return (debug(DBG("Failed to close()")), false);
	cmd_node->ast_cmd.cmd_args[1] = NULL;
	if (dup2(e_data->pipefd[0], STDIN_FILENO) < 0)
		return (debug(DBG("Failed to dup2()")), false);
	if (close(e_data->pipefd[0]) < 0)
		return (debug(DBG("Failed to close()")), false);
	return (true);
}
