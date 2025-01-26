/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:02:36 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/26 01:48:11 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_builtin(t_ast *cmd_node)
{	
	char	*cmd_name;

	if (cmd_node->token != CMD)
		return (-1);
	cmd_name = cmd_node->ast_cmd.cmd_name;
	if (strcmp_ex(cmd_name, "export") && strcmp_ex(cmd_name, "echo") && \
		strcmp_ex(cmd_name, "unset") && strcmp_ex(cmd_name, "exit") && \
		strcmp_ex(cmd_name, "pwd") && strcmp_ex(cmd_name, "env") && \
		strcmp_ex(cmd_name, "cd"))
		return (-1);
	return (1);
}

int	check_and_exec_builtin(t_ast *cmd_node, t_data *data)
{
	if (check_if_builtin(cmd_node) == -1)
		return (-1);
	if (!strcmp_ex(cmd_node->ast_cmd.cmd_name, "export"))
		builtin_export(data, cmd_node);
	else if (!strcmp_ex(cmd_node->ast_cmd.cmd_name, "env"))
		print_env(*data->env);
	else if (!strcmp_ex(cmd_node->ast_cmd.cmd_name, "unset"))
		builtin_unset(data, cmd_node);
	else if (!strcmp_ex(cmd_node->ast_cmd.cmd_name, "pwd"))
		builtin_pwd(data, cmd_node);
	else if (!strcmp_ex(cmd_node->ast_cmd.cmd_name, "exit"))
		builtin_exit(data, cmd_node);
	else if (!strcmp_ex(cmd_node->ast_cmd.cmd_name, "echo"))
		builtin_echo(data, cmd_node);
	else if (!strcmp_ex(cmd_node->ast_cmd.cmd_name, "cd"))
		builtin_cd(data, cmd_node);
	
	return (true);	
}
