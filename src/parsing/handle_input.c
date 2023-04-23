/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:38:03 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/23 22:50:22 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_parse_error(char *str, t_bool clear)
{
	static	t_bool	has_been_printed = false;

	if (str && !has_been_printed)
	{
		printf("%s", str);
		has_been_printed = true;
	}
	if (clear)
		has_been_printed = false;
}

/**
 * @brief Prints a Prompt on the screen and let the user type freely.
 * 		  Stores the line in the history
 * 
 * @return char*, the line read
*/
char	**get_input(void)
{
	char    *raw_input;
	char	*input;
	char	**splitted;

	print_parse_error(NULL, true);
	raw_input = readline("minishell > ");
	if (!raw_input)
		return (NULL);
	/* *** *** *** *** DEBUG *** *** *** *** **/
	/**/if (str_equals(raw_input, "exit")) 	/**/
	/**/{									/**/
	/**/	system("leaks -q minishell");	/**/
	/**/	exit(0);						/**/
	/**/}									/**/
	/* *** *** *** *** DEBUG *** *** *** *** **/
	add_history(raw_input);
	input = join_three(ft_strdup(" "), raw_input, ft_strdup(" "));
	if (!is_valid_input(input))
	{
		free(input);
		return (NULL);
	}
	splitted = ft_split_quote_conscious(input, '|');
	free(input);
	if (!splitted)
		print_parse_error(ERROR_MALLOC, false);
	return (splitted);
}

t_bool is_valid_input(char *line_read)
{
	int	i;
	char **split;
	t_bool	is_valid;

	split = ft_split_quote_conscious(line_read, '|');
	if (!split)
	{
		print_parse_error(ERROR_MALLOC, false);
		return (false);
	}
	i = 0;
	is_valid = true;
	while (split[i])
	{
		if (ft_strlen(split[i]) == 0)
			is_valid = false;
		free(split[i]);
		i++;
	}
	free(split);
	if (!is_valid && i != 1)
		print_parse_error(INV_TKN_MSG"`|'", false);
	return (is_valid);
}

t_cmd	*parse_command(t_env_lst *envp, char *cmd_line)
{
	t_cmd *cmd;
	char **splitted;

	splitted = clean_nulls(ft_split_quote_conscious(cmd_line, ' '));
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!splitted || !cmd)
	{
		print_parse_error(ERROR_MALLOC, false);
		if (cmd)
			free(cmd);
		if (splitted)
			free_str_array(splitted);
		return (NULL);
	}
	cmd->args = splitted;
	if (!fill_redirections(&cmd) || !expand_cmd(&cmd, envp))
	{
		ft_free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
