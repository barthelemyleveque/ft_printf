/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_reco.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:02:11 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/25 18:29:00 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*
** Ft_Append un char
*/

char	*ft_append(char *str, char c)
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
	while (str[y] != '\0')
	{
		copy[y] = str[y];
		y++;
	}
	copy[y] = c;
	copy[y + 1] = '\0';
	free(str);
	return (copy);
}

/*
** Recupere les options : pas besoin des ap
*/

int		ft_option(const char *format, int end, t_var *arg)
{
	char *copy;

	if (format[end] == '0' || format[end] == '#' || format[end] == ' ' ||
		format[end] == '-' || format[end] == '+')
	{
		if (!(copy = ft_append(arg->attribut, format[end])))
			return (-1);
		arg->attribut = copy;
		return (1);
	}
	return (0);
}

/*
** Recupere la width : attention a bien renvoyer le nombre de char donnant
** la width pour eviter les conflits. on commence par verifier que c'est un
** nombre != 0.
*/

int		ft_width(const char *format, int start, t_var *arg)
{
	int		end;
	char	*to_atoi;
	int		i;
	int		width;

	i = 0;
	end = start;
	if (format[end] >= 49 && format[end] <= 57)
	{
		while (format[end] >= 48 && format[end] <= 57)
		{
			end++;
			i++;
		}
		to_atoi = ft_strsub(format, start, i);
		width = ft_atoi(to_atoi);
		arg->width = width;
		free(to_atoi);
	}
	return (i);
}

/*
** Recupere la precision : repere un . et itere tant qu'il y a un chiffre
*/

int		ft_precision(const char *format, int start, t_var *arg)
{
	int		end;
	char	*to_atoi;
	int		i;
	int		precision;

	i = 0;
	end = start;
	if (format[end] == '.')
	{
		end++;
		i++;
		while (format[end] >= 48 && format[end] <= 57)
		{
			end++;
			i++;
		}
		to_atoi = ft_strsub(format, start + 1, i - 1);
		precision = ft_atoi(to_atoi);
		arg->precision = precision;
		free(to_atoi);
	}
	return (i);
}

/*
** Recupere les flags hh l ll L : verifier qu'avant il n'y a pas, au cas ou ce
** soit la conversion
*/

int		ft_flags(const char *format, int start, t_var *arg)
{
	if ((format[start - 1] == 'h' && format[start - 2] == 'h') ||
		(format[start - 1] == 'l' && format[start - 2] == 'l') ||
		(format[start - 1] == 'L'))
		return (0);
	if (format[start] == 'h' || format[start] == 'l' || format[start] == 'L')
	{
		if (!(arg->flags = ft_append(arg->flags, format[start])))
			return (-1);
		return (1);
	}
	return (0);
}
