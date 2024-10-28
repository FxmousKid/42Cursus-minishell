/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:30:29 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/25 18:41:45 by inazaria         ###   ########.fr       */
/*   Updated: 2024/10/24 14:49:56 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analysis.h"
#include "minishell.h"
#include <stdbool.h>

void	init_readline()
{
 	// rl_bind_key('\t', rl_insert);
	rl_bind_key('!', rl_insert);
	using_history();
}

bool	analysis(char *input)
{
	t_lexer lex;
	t_data	data;

	ft_bzero(&lex, sizeof(t_lexer));
	lexer(&lex, input);
	print_lexems(&lex);
	ft_bzero(&data, sizeof(t_data));
	if (!parser(&data, &lex))
		return (debug(DBG("Failed to parser()")), false);
	free_lex(&lex);

	//free_ast(&data->ast);
	//free_data(&data);
	//close_data(&data);
	
	return (true);
}

int	minishell(void)
{
	char	*input;
	int		history_count;

	init_readline();
	history_count = 0;
	while (history_count < 20)
	{
		printf("\n");
		print_prompt();
		input = readline(PROMPT_LINE);
		if (!input)
			break;
		add_history(input);
		history_count++;
		if (!analysis(input))
			return (debug(DBG("Failed to analysis()")), 2);
		free(input);
	}
	clear_history();
 	return (0);
}


int	main(void)
{
	int	minishell_status;

	minishell_status = minishell();
	return (minishell_status);
}


/*
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
	signal(SIGINT, &sig_handler);
	signal(SIGPIPE, &sig_handler);
	data.envir = env;
	data.env = create_env(env);
	create_path(&data);
	ast = test_cmd(&data, ast);
	print_ast(ast);
	find_process(&data, ast);
	return (0);
}
*/


/*
	if (1)
		debug(DBG("Failed to fill condition"));
	print_start_text();
	print_prompt();
	builtin_cd("..");
	printf("\n");
	print_prompt();*/
