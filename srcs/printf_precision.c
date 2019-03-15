/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:41:17 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 16:49:16 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** Gestion de la precision
*/

int		ft_add_precision(t_var *arg)
{
	int		i;
	char	*tmp;

	if (arg->nblong < 0 || arg->nbdouble < 0)
		return (ft_precision_neg(arg));
	if ((ft_check_zero(arg)))
		return (1);
	if (arg->conver == 'p')
		if (!(ft_precision_p(arg)))
			return (-1);
	i = arg->precision - ft_strlen(arg->argtoapp);
	if ((arg->conver == 'd' || arg->conver == 'i' || arg->conver == 'o' ||
		arg->conver == 'u' || arg->conver == 'x' || arg->conver == 'X')
		&& i >= 0)
	{
		i = (ft_check_hashtag(arg) == 1 && arg->conver == 'o') ? i - 1 : i;
		while (i-- > 0)
		{
			if (!(tmp = ft_strjoin("0", arg->argtoapp)))
				return (-1);
			free(arg->argtoapp);
			arg->argtoapp = tmp;
		}
	}
	return (1);
}

/*
** Ajout de la precision pour le flag p
*/

int		ft_precision_p(t_var *arg)
{
	int		i;
	char	*tmp;

	i = (int)arg->precision - ft_strlen(arg->argtoapp);
	while (i > 0 && arg->precision != 0)
	{
		if (!(tmp = ft_append_first('0', arg->argtoapp)))
			return (-1);
		free(arg->argtoapp);
		arg->argtoapp = tmp;
		i--;
	}
	if (!(tmp = ft_strjoin("0x", arg->argtoapp)))
		return (-1);
	free(arg->argtoapp);
	arg->argtoapp = tmp;
	return (1);
}

/*
** Verification que la valeur n'est pas egale a 0 : sinon on remplit avec des
** '\0'
*/

int		ft_check_zero(t_var *arg)
{
	if (arg->precision == 0 && arg->conver != 's' && arg->conver != 'p' &&
		arg->conver != 'c')
	{
		if ((arg->conver == 'd' || arg->conver == 'i') && arg->nblong == 0)
			ft_bzero(arg->argtoapp, ft_strlen(arg->argtoapp));
		else if ((arg->conver == 'o' || arg->conver == 'x' || arg->conver == 'X'
					|| arg->conver == 'u') && arg->unsignedll == 0)
			ft_bzero(arg->argtoapp, ft_strlen(arg->argtoapp));
		else if (arg->conver == 'f' && arg->nbdouble == 0)
			ft_bzero(arg->argtoapp, ft_strlen(arg->argtoapp));
		return (1);
	}
	return (0);
}

/*
** Gestion de la precision pour les int negatifs
*/

int		ft_precision_neg(t_var *arg)
{
	int		i;
	char	*tmp;

	i = arg->precision - ft_strlen(arg->argtoapp);
	if ((arg->conver == 'd' || arg->conver == 'i' || arg->conver == 'o' ||
		arg->conver == 'u' || arg->conver == 'x' || arg->conver == 'X')
		&& i >= 0)
	{
		arg->argtoapp[0] = '0';
		while (i-- > 0)
		{
			if (!(tmp = ft_strjoin("0", arg->argtoapp)))
				return (-1);
			free(arg->argtoapp);
			arg->argtoapp = tmp;
		}
		if (!(tmp = ft_strjoin("-", arg->argtoapp)))
			return (-1);
		free(arg->argtoapp);
		arg->argtoapp = tmp;
	}
	return (1);
}
