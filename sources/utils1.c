/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: adakheel <adakheel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 11:40:39 by adakheel      #+#    #+#                 */
/*   Updated: 2024/06/27 07:57:35 by adakheel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_protect(char *str, t_all *all)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(str);
	if (!temp && errno == 12)
	{
		free(str);
		str = NULL;
		memory_allocation_failed(all);
	}
	return (temp);
}

char	*sub_protect(char *str, t_all *all, int start, int len)
{
	char	*temp;

	temp = NULL;
	temp = ft_substr(str, start, len);
	if (!temp && errno == 12)
	{
		free(str);
		str = NULL;
		memory_allocation_failed(all);
	}
	return (temp);
}

int	is_white_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*p;
	size_t	lens1;
	size_t	lens2;
	size_t	tolen;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	tolen = lens1 + lens2 + 1;
	if (!s1)
		return ((char *) s2);
	if (!s2)
		return ((char *)s1);
	p = (char *)malloc(tolen * (sizeof(char)));
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(p, s1, lens1 + 1);
	ft_strlcpy(p + lens1, s2, lens2 + 1);
	if (s1)
		free(s1);
	return (p);
}

int	ft_strncmp2(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (str1[i] || str2[i]))
	{
		a = str1[i];
		b = str2[i];
		if (!a && b == '=')
			return (0);
		if (a != b)
			return (a - b);
		i++;
	}
	return (str1[i - 1] - str2[i - 1]);
}
