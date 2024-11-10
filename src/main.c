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

char	*read_command(void)
{
	printf("\n");
	print_formatted_cwd();
	return (readline(PS1));
}

// Every return code starting from here and down, will signify a exit code

int	minishell(char *input, t_env *data_env)
{
	t_lexer	lex;
	t_data	data;

	if (*input == '\0')
		return (0);
	ft_bzero(&lex, sizeof(t_lexer));
	lexer(&lex, input);
	print_lexems(&lex);
	ft_bzero(&data, sizeof(t_data));
	data.env = data_env;
	if (!parser(&data, &lex))
	{
		free_lex(&lex);
		return (debug(DBG("Failed to parser()")), 2);
	}

	// if (!exec(data))
	// {
	//		free(...)
	//		...
	//		return (data->exit_code);
	// }	

	free_lex(&lex);
	//free_ast(&data->ast);
	//free_data(&data);
	//close_data(&data);
	
	return (0);
}

int	launch_minishell(char *env[])
{
	t_env	*data_env;
	char	*input;
	int		sh_st;

	data_env = ft_calloc(sizeof(t_env), 1);
	init_env(data_env, env);
	input = read_command();
	while (input)
	{
		add_history(input);
		sh_st = minishell(input, data_env);
		if (sh_st)
		{
			free_env(data_env);
			free(data_env);
			return (free(input), debug(DBG("Failed to minishell()")), sh_st);
		}
		free(input);
		input = read_command();
	}
 	return (free_env(data_env), free(data_env), 0);
}


int	main(int argc, char *argv[], char *env[])
{
	int	minishell_status;

	(void) argc;
	(void) argv;
	init_readline();
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
