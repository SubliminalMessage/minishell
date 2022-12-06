/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:09:20 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/06 20:20:16 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 *  @brief Creates a new envinroment variable struct
 *  
 *  @param str A String, containing the name and value of the variable, 
 *  as found when executing 'export': <NAME>=<VALUE>
 * 
 *  @return A new t_env structure, with the information of the environment var
*/
t_env   *new_env(char *str)
{
    int i;
    t_env   *env;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    env = malloc(sizeof(t_env));
    if (!env)
        return (env);
    env->name = ft_substr(str, 0, i);
    env->value = ft_substr(str, i + 1, ft_strlen(str));
    env->join = ft_strdup(str);
    env->next = NULL;
    return (env);
}

/**
 *  @brief Adds a new 'environment variable' to the end of the list
 * 
 *  @param lst The actual list for the new Variable to be added
 *  @param new The new Variable to be added
 * 
*/
void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*next_elem;

	if (*lst == NULL)
		*lst = new;
	else
	{
		next_elem = *lst;
		while (next_elem->next != NULL)
			next_elem = next_elem->next;
		next_elem->next = new;
	}
}


/**
 *  @brief Frees the environment list created by init_environ()
 * 
 *  @param env_list A pointer to the Environment List to free
*/
void    free_environ(t_env **env_list)
{
    t_env	*next;
    t_env	*temp;

    next = *env_list;
    while (next != NULL)
    {
        free(next->name);
        free(next->value);
        free(next->join);
        temp = next;
        next = next->next;
        free(temp);
    }
    *env_list = NULL;
}

/**
 *  @brief Initializes the Environment List with the system's environment vars
*/
t_env *init_environ(void)
{
    extern char **environ;
    t_env *env_list;
    t_env *new;
    int i;

    i = 0;
    env_list = NULL;
    while (environ[i])
    {
        new = new_env(environ[i]);
        ft_envadd_back(&env_list, new);
        i++;
    }
    return (env_list);
}

/**
 *  @brief Updates an already existing environment variable, or creates it
 * 
 *  @param list The List of environment variables
 *  @param name The name of the variable to update
 *  @param new_value The new value the variable should have
 * 
*/
void    update_env(t_env **list, char *name, char *new_value)
{
    t_env *node;
    char *tmp_name;
    char *tmp_value;

    node = *list;
    while (node)
    {
        if (str_equals(node->name, name) == true)
            break ;
        node = node->next;
    }
    if (node == NULL)
    {
        // strdup on new_value should not be needed, but the test are being made with hardcoded strings. Same thing
        // with ft_strdup(name);
        // ToDo: Remove the ft_strdup(new_value) and ft_strdup(name) and double-check those variables are being both malloc-ed and free-d
        node = new_env(join_three(ft_strdup(name), ft_strdup("="), ft_strdup(new_value))); 
        ft_envadd_back(list, node);
        return ;
    }
    free(node->value);
    node->value = ft_strdup(new_value);
    tmp_name = ft_strdup(node->name);
    tmp_value = ft_strdup(node->value);
    // strdup on new_value should not be needed, but the test are being made with hardcoded strings. Same thing
    // with ft_strdup(name);
    // ToDo: Remove the ft_strdup(new_value) and ft_strdup(name) and double-check those variables are being both malloc-ed and free-d
    node->join = join_three(node->name, ft_strdup("="), node->value);
    node->name = tmp_name;
    node->value = tmp_value;
}