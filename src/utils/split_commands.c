/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:46:22 by dangonza          #+#    #+#             */
/*   Updated: 2022/12/08 16:41:17 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @deprecated This function is deprecated and will be replaced with
 * ft_split_quote_conscious() in the future (or a similar one).
*/

static int	get_total_cmds(const char *s, char c);
static void	inner_whiles(char *s, int *i, char c, size_t *slen);
static char	**free_all(char **words, int saved);

char	**ft_split_cmds(const char *s)
{
	size_t	s_len;
	int		saved;
	int		i;
	char	**words;
	int		total_words;

	if (!s)
		return (NULL);
	total_words = get_total_cmds(s, '|');
	words = malloc(sizeof(char *) * (total_words + 1));
	if (words == NULL)
		return (NULL);
	i = 0;
	saved = -1;
	s_len = 0;
	while (*(s + i) && ++saved < total_words)
	{
		inner_whiles((char *) s, &i, '|', &s_len);
		words[saved] = ft_strtrim_free(ft_substr(s, i, (size_t) s_len), " ");
		if (words[saved] == NULL)
			return (free_all(words, saved));
		i += s_len;
	}
	words[total_words] = NULL;
	return (words);
}

static char	**free_all(char **words, int saved)
{
	int	i;

	i = 0;
	while (i < saved)
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

static void	inner_whiles(char *s, int *i, char c, size_t *slen)
{
	char	in_quote;

	in_quote = '\0';
	if (*(s + (*i)) == c)
		*i = *i + 1;
	*slen = 0;
	while (s[(*i) + (*slen)] != '\0' && (in_quote != '\0' || s[(*i) + (*slen)] != c))
	{
		if (s[(*i) + (*slen)] == '"' || s[(*i) + (*slen)] == '\'')
		{
			if (s[(*i) + (*slen)] == in_quote)
				in_quote = '\0';
			else if (in_quote == '\0')
				in_quote = s[(*i) + (*slen)];
		}
		*slen = *slen + 1;
	}
}

static int	get_total_cmds(const char *s, char c)
{
	int		total;
	int		i;
	char	in_quote;

	if (!(*s))
		return (0);
	total = 0;
	i = 0;
	if (*s != c)
		total++;
	in_quote = '\0';
	while (*(s + i))
	{
		if (*(s + i) == '"' || *(s + i) == '\'')
		{
			if (*(s + i) == in_quote)
				in_quote = '\0';
			else if (in_quote == '\0')
				in_quote = *(s + i);
		}
		if (s[i] == c && s[i + 1] != '\0' && in_quote == '\0')
			total++;
		i++;
	}
	return (total);
}
