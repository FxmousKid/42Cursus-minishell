/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:08:52 by inazaria          #+#    #+#             */
/*   Updated: 2025/02/01 14:46:28 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "macros.h"
#include "minishell.h"

void	builtin_exit_aux(t_data *data, t_ast *cmd_node)
{
	int	idx;
	int	code;

	idx = 0;
	while ((size_t) idx < ft_strlen(cmd_node->ast_cmd.cmd_args[1]))
	{
		if (!ft_isdigit(cmd_node->ast_cmd.cmd_args[1][idx]))
		{
			printf("%s: %s: %s: %s\n", SH_NAME, "exit", \
				cmd_node->ast_cmd.cmd_args[1], "numeric argument required");
			code = 2;
			free_data_w_env(data, NULL);
			exit(code);
		}
		idx++;
	}
}

void	builtin_exit(t_data *data, t_ast *cmd_node)
{
	long int	code;

	printf("exit\n");
	code = 0;
	if (cmd_node->ast_cmd.cmd_args[1])
		code = ft_atoi_long(cmd_node->ast_cmd.cmd_args[1]);
	if (code > INT_MAX || code < 0)
	{
		printf("%s: %s: %s: %s\n", SH_NAME, "exit", \
		cmd_node->ast_cmd.cmd_args[1], "numeric argument required");
		code = 2;
		free_data_w_env(data, NULL);
		exit(code);
	}
	builtin_exit_aux(data, cmd_node);
	free_data_w_env(data, NULL);
	exit(code);
}
