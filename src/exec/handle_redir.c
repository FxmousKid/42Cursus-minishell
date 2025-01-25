/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:30:29 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/25 05:29:05 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "exec.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdbool.h>

int	open_files(t_ast *node, t_exec_data *e_data)
{
	char	*file_name;

	file_name = node->right->ast_file.file_name;
	if (node->token == REDIR_IN)
		e_data->fd_in = open(file_name, O_RDONLY);
	else if (node->token == REDIR_OUT)
		e_data->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token == REDIR_APPEND)
		e_data->fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (e_data->fd_in < 0)
		debug(DBG("Failed to open file for reading"));
	else if (e_data->fd_out < 0)
		debug(DBG("Failed to open file for writing"));
	if (e_data->fd_in < 0 || e_data->fd_out < 0)
	{
		custom_name_perror(file_name);
		return (false);
	}
	return (true);
}

void	emergency_close_files(t_exec_data *e_data)
{
	if (e_data->fd_out)
		close(e_data->fd_out);
	else if (e_data->fd_in)
		close(e_data->fd_in);
}

int	handle_redir(t_data *data, t_ast *node, t_exec_data *e_data)
{
	if (!open_files(node, e_data))
		exit_from_child("Failed to open_files()", data);

	if (!dup_or_cut_tree(node, e_data))
	{
		emergency_close_files(e_data);
		exit_from_child("Failed to dup_or_cut_tree()", data);
	}
	return (true);
	
}
