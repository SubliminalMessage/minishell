/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_main_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:55:26 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/18 00:21:31 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Given an array, and a new element to add, creates a new array
 *        with a size of one more the original, and adds the new element
 *        to the front.
 * 
 * @param array, the array of elements to modify
 * @param element, the new element to add
 * 
 * @return char **, the new array. 
*/
char	**add_array_front(char **array, char *element)
{
	int		size;
	char	**new_array;
	int		i;

	size = ft_arrsize(array);
	new_array = ft_calloc(size + 2, sizeof(char *));
	if (new_array)
	{
		new_array[0] = element;
		i = 0;
		while (++i < (size + 1))
			new_array[i] = array[i - 1];
	}
	free(array);
	return (new_array);
}

/**
 * @brief	Given a list of arguments, gets the argument that is THE command
 *          to execute. This can be tricky, because an environment variable
 *          can expand to a whole command, but only occupy a single command.
 *          E.g.: 'minishell> export test="echo Hello world"'
 * 			This is tricky because not only you have to specify 'echo' is
 *          the main command, but also you have to edit the whole argument
 *          list in order for it to be correct:
 * 			args[0] => 'echo'
 *          args[1] => 'Hello World'
 * 
 * @param arguments, the argument list (Triple Pointer)
 * 
 * @return char *, the Main Command (ft_strdup()-ed). NULL if something went
 *         wrong (plus, an error is shown).
*/
char	*get_main_command(char ***arguments, t_bool is_quoted)
{
	char	*first_arg;
	int		space_idx;
	char	*command;

	first_arg = (*arguments)[0];
	space_idx = ft_strchr(first_arg, ' ') - first_arg;
	if (space_idx < 0 || is_quoted)
		return (ft_strdup(first_arg));
	command = ft_substr(first_arg, 0, space_idx);
	(*arguments)[0] = ft_substr(first_arg, space_idx + 1, ft_strlen(first_arg));
	free(first_arg);
	if (!command || !((*arguments)[0]))
	{
		print_parse_error(ERROR_MALLOC, false);
		return (NULL);
	}
	*arguments = add_array_front(*arguments, command);
	return (ft_strdup(command));
}
