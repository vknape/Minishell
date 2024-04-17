/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vknape <vknape@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:39:33 by vknape            #+#    #+#             */
/*   Updated: 2023/10/25 13:51:36 by vknape           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*cs1;
	char	*cs2;

	cs1 = (char *) s1;
	cs2 = (char *) s2;
	new = (char *)malloc((ft_strlen(cs1) + ft_strlen(cs2) + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, cs1, ft_strlen(cs1) + 1);
	ft_strlcpy(&new[ft_strlen(cs1)], cs2, ft_strlen(cs2) + 1);
	return (new);
}
