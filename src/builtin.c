/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:51:58 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/08 15:30:50 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **arg)
{
	int	n;
	int	i;

	i = 0;
	n = 1;
	if (ft_strncmp(arg[0], "-n", ft_strlen(arg[0])))
	{
			ft_putstr_fd(arg[0], 1);
			i = 1;
			n = 0;
	}
	while (arg[i] != NULL)
	{
		ft_putstr_fd(arg[i], 1);
		i++;
	}
	if (n)
		ft_putstr_fd("\n", 1);
	return (1);
}

int	builtin_pwd(int	i)
{
	char	buf[4096];

	if (getcwd(buf, 4096) == NULL)
		return (perror(""), debug(DBG("Failed to getcwd()")), 0 );
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

int	builtin_cd(char *path)
{
	if (chdir(path) == -1)
		return (perror(""), debug(DBG("Failed to chdir()")), 0);
	return (0);
}