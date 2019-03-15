/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:48:07 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 18:23:27 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "../includes/header.h"

/*
** On a trouve un %, on va maintenant chercher les caracteres autorises en
** boucle :
*/

int		ft_parser(const char *format, int end, t_var *arg)
{
	int	i;

	i = 0;
	if ((i = ft_option(format, end, arg)))
		return (i);
	if ((i = ft_width(format, end, arg)))
		return (i);
	if ((i = ft_precision(format, end, arg)))
		return (i);
	if ((i = ft_flags(format, end, arg)))
		return (i);
	return (i);
}

/*
** Read va permettre de commencer, ou reprendre la lecture apres le %...
** On va recuperer ce qui est lu, puis dispatcher la partie %...
*/

int		ft_read(const char *format, int start, t_var *arg, va_list ap)
{
	int end;
	int	i;

	end = start;
	i = 0;
	while (format[end] != '\0' && format[end] != '%')
		end++;
	end = ft_str(start, end, format, arg);
	if (format[end] == '\0')
		return (end);
	if (format[end] == '%')
	{
		end++;
		while ((i = ft_parser(format, end, arg)))
			end += i;
		if (i == -1)
			return (-1);
		if (!(ft_last_conv(arg, format, end)))
			return (-1);
		if (!(ft_conversions(arg, ap)))
			return (-1);
		if (!(ft_options(arg)))
			return (-1);
	}
	return (end + 1);
}

/*
** ft_str copie les caracteres sans incidence dans la string (= rendu final) de
** de la structure
*/

int		ft_str(int start, int end, const char *format, t_var *arg)
{
	char	*substring;
	char	*tmp;
	int		i;
	int		len;

	i = -1;
	len = end - start;
	if (!(substring = (char*)malloc(sizeof(char) * (len + 1))))
		return (-1);
	while (i++ < (len - 1))
		substring[i] = format[start++];
	substring[i] = '\0';
	if (!(tmp = ft_strjoin(arg->string, substring)))
		return (-1);
	free(substring);
	free(arg->string);
	arg->string = tmp;
	return (end);
}

/*
** Arg-> conver et gestion du %%
*/

int		ft_last_conv(t_var *arg, const char *format, int end)
{
	int		i;
	char	*tmp;

	i = 0;
	if (format[end] == '%')
	{
		if (!(tmp = ft_append(arg->argtoapp, '%')))
			return (-1);
		if (!(arg->argtoapp = ft_strdup(tmp)))
			return (-1);
		free(tmp);
		arg->conver = format[end];
		return (1);
	}
	else
		arg->conver = format[end];
	return (1);
}
