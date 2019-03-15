/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:19:51 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 18:25:01 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** Gestion du %, ajout a la str, et free des arg
*/

int		ft_conversions(t_var *arg, va_list ap)
{
	if (arg->conver == 'd' || arg->conver == 'i')
		ft_conv_int(arg, ap);
	else if (arg->conver == 'o' || arg->conver == 'u' || arg->conver == 'x' ||
		arg->conver == 'X' || arg->conver == 'p')
		ft_conv_unsigned(arg, ap);
	else if (arg->conver == 'f' && arg->flags[0] == 'L')
		arg->nbdouble = va_arg(ap, long double);
	else if (arg->conver == 'f')
		arg->nbdouble = va_arg(ap, double);
	else if (arg->conver == 'c' || arg->conver == 's')
	{
		if (!(ft_goto_cs(arg, ap)))
			return (-1);
	}
	else if (arg->conver != '%')
		if (!(arg->argtoapp = ft_append(arg->argtoapp, arg->conver)))
			return (-1);
	if (!(ft_tostr(arg)))
		return (-1);
	return (1);
}

/*
** Gestion du cas ou on a un '\0' pour l'afficher
*/

int		ft_conv_c(t_var *arg, va_list ap)
{
	int i;

	if ((i = va_arg(ap, int)) != 0)
		arg->nblong = i;
	else if (i == 0)
	{
		arg->count = arg->count + 1 + (arg->width) + ft_strlen(arg->string);
		arg->count = (arg->width >= 2) ? arg->count - 1 : arg->count;
		ft_putstr(arg->string);
		ft_flags_c(arg);
		free(arg->string);
		if (!(arg->string = (char*)malloc(sizeof(char))))
			return (-1);
		arg->string[0] = '\0';
		if (!(ft_restart(arg)))
			return (-1);
	}
	return (1);
}

/*
** Prise en compte du flag '-' dans le cas u '\0'
*/

void	ft_flags_c(t_var *arg)
{
	if (ft_check_0(arg) == 2)
	{
		write(1, "\0", 1);
		while (--arg->width > 0)
			write(1, " ", 1);
	}
	else
	{
		while (--arg->width > 0)
			write(1, " ", 1);
		write(1, "\0", 1);
	}
}

void	ft_conv_int(t_var *arg, va_list ap)
{
	int i;

	i = ft_strlen(arg->flags);
	if (i == 0)
		arg->nblong = va_arg(ap, int);
	else if (i == 1 && arg->flags[0] == 'h')
		arg->nblong = (short int)va_arg(ap, int);
	else if (i == 1 && arg->flags[0] == 'l')
		arg->nblong = va_arg(ap, long);
	else if (i == 2 && arg->flags[0] == 'h' && arg->flags[1] == 'h')
		arg->nblong = (char)va_arg(ap, int);
	else if (i == 2 && arg->flags[0] == 'l' && arg->flags[1] == 'l')
		arg->nblong = va_arg(ap, long long);
}

void	ft_conv_unsigned(t_var *arg, va_list ap)
{
	int	i;

	i = ft_strlen(arg->flags);
	if (arg->conver == 'p')
		arg->unsignedll = va_arg(ap, unsigned long);
	else if (i == 0)
		arg->unsignedll = va_arg(ap, unsigned int);
	else if (i == 1 && arg->flags[0] == 'h')
		arg->unsignedll = (unsigned short int)va_arg(ap, unsigned int);
	else if (i == 1 && arg->flags[0] == 'l')
		arg->unsignedll = va_arg(ap, unsigned long);
	else if (i == 2 && arg->flags[0] == 'h' && arg->flags[1] == 'h')
		arg->unsignedll = (unsigned char)va_arg(ap, unsigned int);
	else if (i == 2 && arg->flags[0] == 'l' && arg->flags[1] == 'l')
		arg->unsignedll = va_arg(ap, unsigned long long);
}
