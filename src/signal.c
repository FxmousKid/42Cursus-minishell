/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:15:11 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/21 19:55:34 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	printf("exit cash\n");
	exit(1);
}

void	sigpipe_handler(int signum)
{
	(void)signum;
	printf("Catch SIGPIPE\n");
}