/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:08:04 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/19 17:33:58 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_tof(t_var *arg)
{
	long long	entiers;
	char		*strent;
	char		*strdeci;

	entiers = (long long)arg->nbdouble;
	if (!(strdeci = ft_decimales_18(arg, entiers, arg->nbdouble)))
		return (-1);
	if (!(strent = ft_entiers_18(arg->nbdouble)))
		return (-1);
	strent = ft_arrondi_entiers(arg, strent, strdeci);
	if (arg->precision != 0)
	{
		if (!(strent = ft_append(strent, '.')))
			return (-1);
		if (!(arg->argtoapp = ft_strjoin(strent, strdeci)))
			return (-1);
	}
	else if (!(arg->argtoapp = ft_strdup(strent)))
		return (-1);
	free(strent);
	free(strdeci);
	return (1);
}

char	*ft_decimales_18(t_var *arg, long long sub, long double copy)
{
	int		tmp;
	int		i;
	int		c;
	char	*str;

	c = 0;
	i = 6;
	if (!(str = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	str[0] = '\0';
	if (arg->precision >= 0)
		i = arg->precision;
	copy = copy - sub;
	copy = (copy < 0) ? -copy : copy;
	while (c++ <= i)
	{
		copy = copy * 10;
		if (!(str = ft_append(str, (int)copy + 48)))
			return (NULL);
		tmp = (int)copy;
		copy = copy - tmp;
	}
	str = ft_arrondi_decimales(arg, str);
	return (str);
}

char	*ft_entiers_18(long double copy)
{
	int		i;
	int		c;
	char	*str;

	i = 0;
	c = 0;
	if (!(str = (char*)malloc(sizeof(char) * 2)))
		return (NULL);
	str[0] = (copy < 0 ? '-' : '\0');
	str[1] = '\0';
	copy = (copy < 0 ? -copy : copy);
	while (copy >= 10)
	{
		copy = copy / 10;
		i++;
	}
	while (c++ <= i)
	{
		if (!(str = ft_append(str, (int)copy + 48)))
			return (NULL);
		copy = (copy - (int)copy) * 10;
	}
	return (str);
}

char	*ft_arrondi_decimales(t_var *arg, char *str)
{
	int	i;
	int c;

	i = 6;
	if (arg->precision > -1)
		i = arg->precision;
	c = i;
	if (str[i] >= '5')
	{
		while (str[c - 1] == '9')
		{
			str[c - 1] = '0';
			c--;
		}
		str[c - 1] += 1;
	}
	if (i != 0)
		str[i] = '\0';
	return (str);
}

/*
** Arrondi des entiers dans le cas ou precision = 0
*/

char	*ft_arrondi_entiers(t_var *arg, char *entiers, char *deci)
{
	int	i;

	i = ft_strlen(entiers) - 1;
	if (deci[0] >= '5' && arg->precision == 0)
	{
		while (entiers[i] == '9')
		{
			entiers[i] = '0';
			i--;
		}
		entiers[i] += 1;
	}
	return (entiers);
}
