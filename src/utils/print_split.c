/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:57:58 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/15 16:52:29 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **split)
{
	int		idx;

	printf("%sArray%s : [", GREEN_TXT, END_TXT);
	idx = 0;
	while (split[idx + 1])
	{
		printf("%s%s%s, ", YELLOW_TXT, split[idx], END_TXT);
		idx++;
	}
	printf("%s%s%s]\n", YELLOW_TXT, split[idx], END_TXT);
}
