/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_restart.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:11:53 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 16:45:04 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		ft_restart(t_var *arg)
{
	if (arg->conver == 's')
		ft_strdel(&arg->s);
	arg->width = 0;
	arg->precision = -1;
	arg->conver = 0;
	arg->nblong = 0;
	arg->nbdouble = 0;
	arg->unsignedll = 0;
	free(arg->argtoapp);
	free(arg->attribut);
	free(arg->flags);
	if (!(arg->attribut = (char*)malloc(sizeof(char) * 1)))
		return (0);
	arg->attribut[0] = '\0';
	if (!(arg->flags = (char*)malloc(sizeof(char) * 1)))
		return (0);
	arg->flags[0] = '\0';
	if (!(arg->argtoapp = (char*)malloc(sizeof(char) * 1)))
		return (0);
	arg->argtoapp[0] = '\0';
	return (1);
}

void	ft_free_for_all(t_var *arg)
{
	ft_strdel(&arg->string);
	free(arg->argtoapp);
	free(arg->attribut);
	free(arg->flags);
	free(arg);
}
