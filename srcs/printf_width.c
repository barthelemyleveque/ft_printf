/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:08:17 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 18:43:35 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** Verif du flag 0
*/

int		ft_check_0(t_var *arg)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (arg->attribut[i] != '\0')
	{
		if (arg->attribut[i] == '-')
			return (2);
		if (arg->attribut[i] == '0')
			c++;
		i++;
	}
	if (c > 0 && arg->precision == -1)
		return (1);
	if (c > 0 && arg->conver == 'f')
		return (1);
	return (0);
}

/*
** Gestion de la width en fonction des flags 0 -
*/

int		ft_add_width(t_var *arg)
{
	char	w;
	char	*tmp;
	int		i;

	w = (ft_check_0(arg) == 1) ? '0' : ' ';
	if ((arg->nblong < 0 || arg->nbdouble < 0) && ft_check_0(arg) != 2)
	{
		i = ft_width_neg(arg, w);
		return (i);
	}
	if ((i = ft_go_width(arg)) && ft_check_0(arg) != 2)
		while (i-- > 0)
		{
			if (!(tmp = ft_append_first(w, arg->argtoapp)))
				return (-1);
			free(arg->argtoapp);
			arg->argtoapp = tmp;
		}
	else if (!(ft_width_minus(arg)))
		return (-1);
	return (1);
}

/*
** GO pour width
*/

int		ft_go_width(t_var *arg)
{
	int	i;

	i = arg->width - ft_strlen(arg->argtoapp);
	if (i <= 0)
		return (0);
	return (i);
}

/*
** Gestion de la width pour les negatifs
*/

int		ft_width_neg(t_var *arg, char w)
{
	int		i;
	char	*tmp;

	if ((i = ft_go_width(arg)) && ft_check_0(arg) == 0)
	{
		arg->argtoapp[0] = (ft_check_0(arg) == 1) ? '0' : arg->argtoapp[0];
		while (i-- > 0)
		{
			if (!(tmp = ft_append_first(w, arg->argtoapp)))
				return (-1);
			free(arg->argtoapp);
			arg->argtoapp = tmp;
		}
	}
	else if ((i = ft_go_width(arg)) && ft_check_0(arg) == 1)
	{
		if (!(ft_width_neg_bis(arg, w, i)))
			return (-1);
	}
	return (1);
}

/*
** Rajouter un char au debut de la str
*/

char	*ft_append_first(char c, char *str)
{
	int		i;
	int		y;
	char	*copy;

	i = 0;
	y = 0;
	while (str[i] != '\0')
		i++;
	if (!(copy = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	copy[y] = c;
	y++;
	while (str[y - 1] != '\0')
	{
		copy[y] = str[y - 1];
		y++;
	}
	copy[y] = '\0';
	return (copy);
}
