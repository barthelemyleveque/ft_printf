/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:35:25 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 16:09:30 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "../includes/header.h"

/*
** Initialisation des variables numeriques de la structure et on garde pos
*/

void	init_vars(t_var *arg)
{
	arg->width = 0;
	arg->precision = -1;
	arg->conver = 0;
	arg->nblong = 0;
	arg->nbdouble = 0;
	arg->unsignedll = 0;
	arg->count = 0;
}

/*
** Initialise les variables devant etre malloc : story (= le format) et
** str (ce qui sera imprime)
*/

int		init_arg(const char *format, t_var *arg)
{
	int		i;
	int		c;

	i = 0;
	c = -1;
	while (format[i] != '\0')
		i++;
	if (!(arg->string = (char*)malloc(sizeof(char) * 1)))
		return (0);
	arg->string[0] = '\0';
	if (!(arg->attribut = (char*)malloc(sizeof(char) * 1)))
		return (0);
	arg->attribut[0] = '\0';
	if (!(arg->flags = (char*)malloc(sizeof(char) * 1)))
		return (0);
	arg->flags[0] = '\0';
	if (!(arg->argtoapp = (char*)malloc(sizeof(char) * 1)))
		return (0);
	arg->argtoapp[0] = '\0';
	init_vars(arg);
	return (1);
}

/*
** Lance la fonction et lance l'initialisation
*/

int		ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	int		i;
	int		c;
	t_var	*arg;

	va_start(ap, format);
	i = 0;
	c = ft_strlen(format);
	if (!(arg = (t_var*)malloc(sizeof(t_var) * 1)) || !(init_arg(format, arg)))
		return (0);
	while (format[i] != '\0' && i <= c && i != -1)
		i = ft_read(format, i, arg, ap);
	va_end(ap);
	i = ft_strlen(arg->string);
	if (i != -1)
		ft_putstr(arg->string);
	i = i + arg->count;
	ft_free_for_all(arg);
	return (i);
}
