/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_width_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:39:46 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 18:42:54 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** On passe le flag -
*/

int		ft_width_minus(t_var *arg)
{
	char	*tmp;
	int		i;

	i = arg->width - ft_strlen(arg->argtoapp);
	if (ft_check_0(arg) == 2 && i >= 0)
	{
		while (i-- > 0)
		{
			if (!(tmp = ft_append(arg->argtoapp, ' ')))
				return (-1);
			arg->argtoapp = tmp;
		}
	}
	return (1);
}

/*
** Gestion du flag '0' et ' ' en cas de width et nombre positif.
*/

int		ft_exceptions(t_var *arg)
{
	if ((arg->conver == 'i' || arg->conver == 'd' || arg->conver == 'f')
			&& (ft_check_0(arg) == 1))
	{
		if (ft_check_space(arg) >= 1 && arg->nblong >= 0 && arg->nbdouble >= 0)
			arg->width -= 1;
		if (!(ft_add_width(arg)))
			return (-1);
		if (!(ft_space(arg)))
			return (-1);
		return (1);
	}
	else if ((arg->conver == 'x' || arg->conver == 'X') && ft_check_0(arg) == 1)
	{
		if (ft_check_hashtag(arg))
			arg->width -= 2;
		if (!(ft_add_width(arg)))
			return (-1);
		if (!(ft_hashtag_x(arg)))
			return (-1);
		if (!(ft_space(arg)))
			return (-1);
		return (1);
	}
	return (0);
}

/*
** Check du # present
*/

int		ft_check_hashtag(t_var *arg)
{
	int i;

	i = 0;
	while (arg->attribut[i] != '\0')
	{
		if (arg->attribut[i] == '#')
			return (1);
		i++;
	}
	return (0);
}

/*
** Fonction de norme ...
*/

int		ft_goto_cs(t_var *arg, va_list ap)
{
	if (arg->conver == 'c')
	{
		if (!(ft_conv_c(arg, ap)))
			return (-1);
	}
	else if (arg->conver == 's')
	{
		if (!(arg->s = va_arg(ap, char *)))
		{
			if (!(arg->s = ft_strdup("(null)")))
				return (-1);
		}
		else if (!(arg->s = ft_strdup(arg->s)))
			return (-1);
	}
	return (1);
}

/*
** Fonction de norme
*/

int		ft_width_neg_bis(t_var *arg, char w, int i)
{
	char	*tmp;

	arg->argtoapp[0] = '0';
	while (i-- > 0)
	{
		if (!(tmp = ft_append_first(w, arg->argtoapp)))
			return (-1);
		free(arg->argtoapp);
		arg->argtoapp = tmp;
	}
	arg->argtoapp[0] = '-';
	return (1);
}
