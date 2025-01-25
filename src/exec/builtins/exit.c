/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:08:52 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/25 08:06:19 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_data *data, t_ast *cmd_node)
{
	int	code;

	printf("exit\n");
	code = 0;
	if (cmd_node->ast_cmd.cmd_args[1])
		code = ft_atoi(cmd_node->ast_cmd.cmd_args[1]);
	free_data_w_env(data, NULL);
	exit(code);
}
