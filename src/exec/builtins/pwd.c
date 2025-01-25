/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:01:16 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/25 06:01:40 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_data *data, t_ast *node)
{
	char	*pwd;

	(void)node;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		custom_name_error("pwd", strerror(errno));
		data->exit_code = EXIT_FAILURE;
		return (false);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (true);
}
