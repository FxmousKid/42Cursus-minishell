/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:29:37 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:47:43 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdbool.h>

void	proper_print(char *str)
{
	if (str[0] == '"' || str[0] == '\'')
	{
		str++;
		str[ft_strlen(str) - 1] = '\0';
		printf("%s", str);
		str[ft_strlen(str)] = str[0];
	}
	else
		printf("%s", str);
}

int	builtin_echo(t_data *data, t_ast *node)
{
	char	**args;
	int		i;
	bool	trail;

	(void)data;
	args = node->ast_cmd.cmd_args;
	trail = strcmp_ex(args[1], "-n");
	i = 1 + (trail == 0);
	while (args[i])
	{
		proper_print(args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (trail)
		printf("\n");
	return (true);
}
