/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:15:24 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/09 19:55:31 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_start_text(void)
{
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", START_TEXT_1,
		START_TEXT_2, START_TEXT_3, START_TEXT_4, START_TEXT_5, START_TEXT_6,
		START_TEXT_7, START_TEXT_8, START_TEXT_9, START_TEXT_10, START_TEXT_11,
		START_TEXT_12, START_TEXT_13, START_TEXT_14, START_TEXT_15, START_TEXT_16,
		START_TEXT_17, START_TEXT_18, START_TEXT_19, START_TEXT_20, START_TEXT_21,
		START_TEXT_22, START_TEXT_23, START_TEXT_24);
}

static int	reduce_home_into_tilde(char *cwd, char *new_cwd)
{
	int	len_home;

	if (strncmp(cwd, "/home/", 6))
		return (0);
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
