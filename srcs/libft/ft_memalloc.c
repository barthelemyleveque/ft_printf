/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:19:48 by bleveque          #+#    #+#             */
/*   Updated: 2018/11/17 15:44:20 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*area;
	int		i;

	i = 0;
	if (!(area = (void*)malloc(sizeof(void) * size)))
		return (NULL);
	ft_bzero(area, size);
	return (area);
}
