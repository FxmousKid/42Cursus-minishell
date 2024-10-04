/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:51:58 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/04 22:47:27 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buildin_echo(char **arg)
{
	if (arg[1] == NULL)
	{
		ft_putstr_fd(arg[0], 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		if (arg[0][1] == 'n')
			ft_putstr_fd(arg[1], 1);
		else
			return (debug(DBG("Wrong option echo")), 0);
	}
	return (1);
}

int	buildin_pwd(int	i)
{
	char	buf[i];

	if (getcwd(buf, i) == NULL)
	{
		if (errno == ERANGE)
		{
			buildin_pwd(i + 1);
			return (1);
		}
		return (debug(DBG("Failed to get the path of the working directory")), 0 );
	}
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

int	buildin_cd(char *path)
{
	if (chdir(path) == -1)
		return (debug(DBG("Failed to cd into the path")), 0);
	return (0);
}