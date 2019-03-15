/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_edit_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:23:46 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 18:43:13 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** Gere les flags # + space, et reste - et 0 a faire en // de la width
*/

int		ft_options(t_var *arg)
{
	char	*tmp;

	if (!(ft_add_precision(arg)))
		return (-1);
	if (ft_exceptions(arg) == 0)
	{
		if (arg->conver == 'x' || arg->conver == 'X')
			if (!(ft_hashtag_x(arg)))
				return (-1);
		if (!(ft_hashtag(arg)))
			return (-1);
		if (!(ft_space(arg)))
			return (-1);
		if (!(ft_add_width(arg)))
			return (-1);
	}
	tmp = arg->string;
	if (!(arg->string = ft_strjoin(arg->string, arg->argtoapp)))
		return (-1);
	ft_strdel(&tmp);
	if (!(ft_restart(arg)))
		return (-1);
	return (1);
}

/*
** En absence du flag '+' on applique aux nb neg : '-' et pour les positifs
*/

int		ft_space(t_var *arg)
{
	char	*tmp;

	if (ft_check_space(arg) == 1 && arg->nblong >= 0 && arg->nbdouble >= 0 &&
		arg->conver != '%')
	{
		if (!(tmp = ft_strjoin(" ", arg->argtoapp)))
			return (-1);
		free(arg->argtoapp);
		arg->argtoapp = tmp;
	}
	else if (ft_check_space(arg) == 2 && arg->nblong >= 0 && arg->nbdouble >= 0)
	{
		if (!(tmp = ft_strjoin("+", arg->argtoapp)))
			return (-1);
		free(arg->argtoapp);
		arg->argtoapp = tmp;
	}
	return (1);
}

/*
** Verification de la prise en compte du flag space, si pas de + dans la chaine
*/

int		ft_check_space(t_var *arg)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (arg->conver != 'd' && arg->conver != 'i' && arg->conver != 'x'
		&& arg->conver != 'X' && arg->conver != 'f')
		return (0);
	while (arg->attribut[i] != '\0')
	{
		if (arg->attribut[i] == '+')
			return (2);
		else if (arg->attribut[i] == ' ')
			c++;
		i++;
	}
	if (c > 0)
		return (1);
	return (0);
}

/*
** Application du flag hastag
*/

int		ft_hashtag(t_var *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg->attribut[i] != '\0')
	{
		if (arg->attribut[i] == '#' && arg->conver == 'f' && arg->precision
			== 0)
		{
			if (!(arg->argtoapp = ft_append(arg->argtoapp, '.')))
				return (-1);
			break ;
		}
		else if (arg->attribut[i] == '#' && arg->conver == 'o' &&
				(arg->unsignedll != 0 || arg->precision == 0))
		{
			if (!(tmp = ft_strjoin("0", arg->argtoapp)))
				return (-1);
			free(arg->argtoapp);
			arg->argtoapp = tmp;
			break ;
		}
		i++;
	}
	return (1);
}

/*
** Application du flag hashtag aux x and X
*/

int		ft_hashtag_x(t_var *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg->attribut[i] != '\0' && arg->unsignedll != 0)
	{
		if (arg->attribut[i] == '#' && arg->conver == 'x')
		{
			if (!(tmp = ft_strjoin("0x", arg->argtoapp)))
				return (-1);
			free(arg->argtoapp);
			arg->argtoapp = tmp;
			break ;
		}
		else if (arg->attribut[i] == '#' && arg->conver == 'X')
		{
			if (!(tmp = ft_strjoin("0X", arg->argtoapp)))
				return (-1);
			free(arg->argtoapp);
			arg->argtoapp = tmp;
			break ;
		}
		i++;
	}
	return (1);
}
