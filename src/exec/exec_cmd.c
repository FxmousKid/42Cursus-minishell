/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 06:06:21 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/13 18:10:26 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "exec.h"
#include "minishell.h"
#include <fcntl.h>

int	exec_cmd_node(t_ast *node)
{
	(void) node;

	return (true);
}

void	check_to_open_files(t_ast *node, t_exec_data *e_data)
{
	char	*file_name;

	if (!is_tok_redir_type(node->token))
		return ;
	if (node->token == REDIR_IN)
	{
		file_name = node->ast_redir_out.right->ast_file.file_name;
		e_data->fd_out = open(file_name, O_RDWR | O_CREAT);
	}
	else if (node->token == REDIR_IN)
	{
		file_name = node->ast_redir_in.right->ast_file.file_name;
		e_data->fd_in = open(file_name, O_RDONLY);
	}
	else if (node->token == REDIR_APPEND)
	{
		file_name = node->ast_redir_append.right->ast_file.file_name;
		e_data->fd_out = open(file_name, O_RDWR | O_APPEND | O_CREAT);
	}
}
