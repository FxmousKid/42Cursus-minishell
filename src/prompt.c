/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:15:24 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/05 23:59:43 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reduce_home_into_tilde(char *cwd, char *new_cwd)
{
	int	len_home;

	(void) new_cwd;

	if (strncmp(cwd, "/home/", 6))
		return (0) ;
	len_home = ft_strlen_till_char(cwd + 6, '/');
	new_cwd[0] = '~';
	ft_strlcpy(new_cwd + 1, cwd + 6 + len_home, MAX_PATH);
	return (1);
	
}

void	print_prompt(void)
{
	char	cwd[PATH_MAX];
	char	tilde_cwd[PATH_MAX];

	ft_bzero(cwd, PATH_MAX * sizeof(char));
	if (!getcwd(cwd, PATH_MAX))
		debug(DBG("get the current path"));
	if (!reduce_home_into_tilde(cwd, tilde_cwd))
		printf("%s%s%s%s", BLUE_TXT, cwd, "\n", END_TXT);
	else
		printf("%s%s%s%s", BLUE_TXT, tilde_cwd, "\n", END_TXT);
	printf("%s %s", PROMPT_SH_NAME, PROMPT);
}
