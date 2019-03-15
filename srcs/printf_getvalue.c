/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_go.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:23:38 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 18:31:56 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** Nous allons convertir le nombre en char* pour pouvoir l'integrer :
*/

int		ft_tostr(t_var *arg)
{
	int	i;

	i = 1;
	if (arg->conver == 'd' || arg->conver == 'i' || arg->conver == 'o' ||
		arg->conver == 'x' || arg->conver == 'X')
		i = ft_toitoa(arg);
	else if (arg->conver == 'c' || arg->conver == 's')
		i = ft_tocs(arg);
	else if (arg->conver == 'f')
		i = ft_tof(arg);
	else if (arg->conver == 'u')
		i = ft_togetu(arg);
	else if (arg->conver == 'p')
		i = ft_adress(arg);
	return (i);
}

int		ft_tocs(t_var *arg)
{
	char	*tmp;

	if (arg->conver == 'c')
	{
		if (!(arg->argtoapp = ft_append(arg->argtoapp, arg->nblong)))
			return (-1);
	}
	else if (arg->conver == 's')
	{
		if (arg->precision >= 0)
		{
			if (!(tmp = ft_strsub(arg->s, 0, arg->precision)))
				return (-1);
		}
		else
		{
			if (!(tmp = ft_strdup(arg->s)))
				return (-1);
		}
		free(arg->argtoapp);
		arg->argtoapp = tmp;
	}
	return (1);
}

int		ft_toitoa(t_var *arg)
{
	char	*tmp;

	free(arg->argtoapp);
	if (arg->conver == 'd' || arg->conver == 'i')
		if (!(arg->argtoapp = ft_itoa_base(arg->nblong, "0123456789")))
			return (-1);
	if (arg->conver == 'o')
		if (!(arg->argtoapp = ft_itoa_us_base(arg->unsignedll, "01234567")))
			return (-1);
	if (arg->conver == 'x')
	{
		if (!(tmp = ft_strdup(arg->attribut)))
			return (-1);
		if (!(arg->argtoapp = ft_itoa_us_base(arg->unsignedll,
						"0123456789abcdef")))
			return (-1);
		free(arg->attribut);
		arg->attribut = tmp;
	}
	if (arg->conver == 'X')
		if (!(arg->argtoapp = ft_itoa_us_base(arg->unsignedll,
						"0123456789ABCDEF")))
			return (-1);
	return (1);
}

int		ft_togetu(t_var *arg)
{
	char	*tmp;

	if (!(tmp = ft_itoa_us_base(arg->unsignedll, "0123456789")))
		return (-1);
	free(arg->argtoapp);
	arg->argtoapp = tmp;
	return (1);
}

int		ft_adress(t_var *arg)
{
	char *tmp;

	free(arg->argtoapp);
	if (arg->unsignedll == 0 && arg->precision != 0)
	{
		if (!(arg->argtoapp = ft_strdup("0")))
			return (-1);
		return (1);
	}
	if (arg->unsignedll == 0 && arg->precision == 0)
	{
		if (!(arg->argtoapp = ft_strdup("")))
			return (-1);
		return (1);
	}
	if (!(tmp = ft_itoa_us_base(arg->unsignedll, "0123456789abcdef")))
		return (-1);
	arg->argtoapp = tmp;
	return (1);
}
