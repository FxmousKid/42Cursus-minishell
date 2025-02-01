/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:57:58 by inazaria          #+#    #+#             */
/*   Updated: 2024/12/18 07:01:06 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **split, char *name)
{
	int		idx;

	printf("%s%s%s : [", GREEN_TXT, name, END_TXT);
	idx = 0;
	while (split[idx + 1])
	{
		printf("%s%s%s, ", YELLOW_TXT, split[idx], END_TXT);
		idx++;
	}
	printf("%s%s%s]\n", YELLOW_TXT, split[idx], END_TXT);
}
