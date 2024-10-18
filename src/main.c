/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:30:29 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/18 21:02:46 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_pair	*create_env(char **env)
{
	t_env_pair	*envir;
	char		**s;
	int			i;

	i = 0;
	envir = malloc(sizeof(t_env_pair) * 1);
	envir->value = malloc(sizeof(char *) * 4096);
	while (env[i])
	{
		s = ft_split(env[i], '=');
		envir->key[i] = s[0];
		envir->value[i] = s[1];
		i++;
	}
	return (envir);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_ast	*ast;

	ast = NULL;
	(void)ac;
	(void)av;
	data.envir = env;
	data.env = create_env(env);
	create_path(&data);
	ast = test_cmd(&data, ast);
	print_ast(ast);
	find_process(&data, ast);
/*
	if (1)
		debug(DBG("Failed to fill condition"));
	print_start_text();
	print_prompt();
	builtin_cd("..");
	printf("\n");
	print_prompt();*/
	return (0);
}
