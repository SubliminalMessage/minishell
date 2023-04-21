/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:38:03 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/22 01:36:36 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		printf(ERROR_MALLOC);
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
		printf(ERROR_MALLOC);
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
		printf(INVALID_TOKEN_CHR, '|');
	return (is_valid);
}

t_bool is_redirection(char *string)
{
	if (!string)
		return (false);
	return (str_equals(string, ">") || str_equals(string, ">>") || str_equals(string, "<") || str_equals(string, "<<"));
}

int	get_redirection_type(char *redirection)
{
	if (str_equals(redirection, ">"))
		return (TRUNC_FTYPE);
	if (str_equals(redirection, ">>"))
		return (APPEND_FTYPE);
	if (str_equals(redirection, "<"))
		return (READ_FTYPE);
	if (str_equals(redirection, "<<"))
		return (HEREDOC_FTYPE);
	return (INVALID); // Should never be reached
}

t_bool save_redirection(t_cmd **cmd, char *redirection, char *redirects_to)
{
	int	redirection_type;
	t_file	*file;

	if (!redirects_to || redirects_to[0] == '>' || redirects_to[0] == '<')
	{
		if (!redirects_to)
			printf(INVALID_TOKEN_STR, "\\n");
		else
			printf(INVALID_TOKEN_CHR, redirects_to[0]);
		return (false);
	}
	redirection_type = get_redirection_type(redirection);
	file = ft_newfile(redirects_to, redirection_type);
	if (!file)
	{
		printf(ERROR_MALLOC);
		return (false);
	}
	if (redirection_type == TRUNC_FTYPE || redirection_type == APPEND_FTYPE)
		ft_lstadd_back(&(*cmd)->out, ft_lstnew(file));
	else if (redirection_type == READ_FTYPE || redirection_type == HEREDOC_FTYPE)
		ft_lstadd_back(&(*cmd)->in, ft_lstnew(file));
	return (true);
}

t_bool	fill_redirections(t_cmd **cmd, char ***str_array)
{
	char **argv;
	int	i;

	argv = *str_array;
	i = -1;
	while (argv[++i])
	{
		if (is_redirection(argv[i]))
		{
			if (save_redirection(cmd, argv[i], argv[i + 1]))
			{
				free(argv[i]);
				argv[i] = ft_strdup(""); // Places a '\0' on that position
				argv[++i] = ft_strdup(""); // clean_nulls() will delete these two after
			}
			else
				return (false);
		}
	}
	*str_array = clean_nulls(*str_array);
	return (true);
}

t_cmd	*parse_command(char *cmd_line)
{
	t_cmd *cmd;
	char **splitted;

	splitted = clean_nulls(ft_split_quote_conscious(cmd_line, ' '));
	if (!splitted)
	{
		printf(ERROR_MALLOC);
		return (NULL);
	}
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		printf(ERROR_MALLOC);
		return (NULL);
	}
	if (!fill_redirections(&cmd, &splitted))
	{
		ft_free_cmd(cmd);
		return (NULL);
	}
	cmd->args = splitted;
	return (cmd);
}
