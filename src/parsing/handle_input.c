/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:38:03 by dangonza          #+#    #+#             */
/*   Updated: 2023/04/21 19:19:50 by dangonza         ###   ########.fr       */
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
		printf(INVALID_TOKEN, '|');
	return (is_valid);
}