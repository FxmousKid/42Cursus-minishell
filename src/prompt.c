/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:15:24 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/10 02:04:32 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_start_text(void)
{
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		START_TEXT1, START_TEXT2, START_TEXT3, START_TEXT4, START_TEXT5,
		START_TEXT6, START_TEXT7, START_TEXT8, START_TEXT9, START_TEXT10,
		START_TEXT11, START_TEXT12, START_TEXT13, START_TEXT14, START_TEXT15,
		START_TEXT16, START_TEXT17, START_TEXT18, START_TEXT19, START_TEXT20,
		START_TEXT21, START_TEXT22, START_TEXT23, START_TEXT24, START_TEXT25,
		START_TEXT26, START_TEXT27, START_TEXT28, START_TEXT29, START_TEXT30,
		START_TEXT31);
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		START_TEXT32, START_TEXT33, START_TEXT34, START_TEXT35,
		START_TEXT36, START_TEXT37, START_TEXT38, START_TEXT39, START_TEXT40,
		START_TEXT41, START_TEXT42, START_TEXT43, START_TEXT44, START_TEXT45,
		START_TEXT46, START_TEXT47, START_TEXT48, START_TEXT49, START_TEXT50,
		START_TEXT51, START_TEXT52, START_TEXT53, START_TEXT54, START_TEXT55,
		START_TEXT56, START_TEXT57, START_TEXT58, START_TEXT59, START_TEXT60,
		START_TEXT61, START_TEXT62);
	printf("%s%s%s", START_TEXT63, START_TEXT64, START_TEXT65);
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
