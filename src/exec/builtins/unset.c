/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:05:29 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/25 06:07:38 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_unset(t_data *data, t_ast *node)
{
	char	*key;

	key = node->ast_cmd.cmd_args[1];
	if (!key)
		return (debug(DBG("No key to unset")), false);
	remove_env_entry(data->env, key);
	return (true);
}
