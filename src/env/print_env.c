/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:00:51 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:34:43 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env env)
{
	int	idx;

	idx = 0;
	printf("%s===Environement Variables Status %s", YELLOW_TXT, END_TXT);
	printf("[%d]%s===%s\n", env.env_len, YELLOW_TXT, END_TXT);
	while (idx < env.env_len)
	{
		printf("===[%s%s%s]", YELLOW_TXT, env.env_pairs[idx].key, END_TXT);
		printf(" ----> ");
		printf("[%s%s%s]", GREEN_TXT, env.env_pairs[idx].value, END_TXT);
		printf("%s===%s\n", YELLOW_TXT, END_TXT);
		idx++;
	}
	printf("%s===Environement Variables Status===%s\n\n", YELLOW_TXT, END_TXT);
}
