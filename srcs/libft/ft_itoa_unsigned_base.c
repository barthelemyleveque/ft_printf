/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:35:20 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 17:10:53 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long			ft_base_check(const char *base)
{
	long long	i;
	long long	j;

	i = 1;
	if (!base)
		return (0);
	if (ft_strlen(base) < 2)
	{
		ft_putstr("Fail : Your base must have at least 2 char\n");
		return (0);
	}
	while (base[i] != '\0')
	{
		j = -1 + i;
		while (base[++i])
		{
			if (base[i] == base[j])
			{
				ft_putstr("Fail : Your base must have different chars\n");
				return (0);
			}
		}
		i = ++j + 1;
	}
	return (1);
}

static unsigned long long	ft_maxpow(unsigned long long nb,
		unsigned long long baselen)
{
	unsigned long long	i;

	i = 0;
	while (nb > baselen)
	{
		nb = nb / baselen;
		i++;
	}
	if (nb == baselen)
		i++;
	return (i);
}

static unsigned long long	ft_powerbase(unsigned long long nb,
		unsigned long long power)
{
	if (nb == 1)
		return (1);
	else if (power == 0)
		return (1);
	else
		return (nb * ft_powerbase(nb, power - 1));
}

char						*ft_itoa_us_base(unsigned long long nb,
															const char *base)
{
	size_t					base_len;
	char					*str;
	unsigned long long		i;
	unsigned long long		c;

	if (!(ft_base_check(base)))
		return (NULL);
	base_len = ft_strlen(base);
	i = ft_maxpow(nb, base_len);
	if (!(str = (char*)ft_memalloc(sizeof(char) * i + 2)))
		return (NULL);
	c = 0;
	while ((i + 1) > 0)
	{
		str[c] = base[(nb / ft_powerbase(base_len, i))];
		nb = nb % ft_powerbase(base_len, i--);
		c++;
	}
	str[c] = '\0';
	return (str);
}
