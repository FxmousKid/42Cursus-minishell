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

// Every return code starting from here and down, will signify a exit code

int	minishell(char *readline_input, t_env *data_env)
{
	static t_data	data = {0};

	if (!readline_input || !*readline_input)
		return (debug(DBG("Received null in readline")), 0);
	free_and_init_data(&data, NULL);
	lexer(&data.lex, readline_input);
	data.env = data_env;
	if (!parser(&data, &data.lex))
	{
		free_and_init_data(&data, readline_input);
		data.exit_code = 2;
		return (debug(DBG("Failed to parse")), 0);
	}
	print_lexems(&data.lex);
	free_and_init_data(&data, readline_input);
	return (0);
}

int	launch_minishell(char *env[])
{
	t_env	*data_env;
	char	*input;

	data_env = ft_calloc(sizeof(t_env), 1);
	init_env(data_env, env);
	input = read_command();
	while (input)
	{
		add_history(input);
		minishell(input, data_env);
		input = read_command();
	}
	printf("exit\n");
 	return (free_env(data_env), 0);
}

int g_signal_received = 0;

int	main(int argc, char *argv[], char *env[])
{
	int	minishell_status;

	(void) g_signal_received;
	(void) argc;
	(void) argv;
	init_readline();
	setup_signals();
	minishell_status = launch_minishell(env);
	return (minishell_status);
}

/*
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
