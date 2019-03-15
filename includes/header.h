/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleveque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:32:35 by bleveque          #+#    #+#             */
/*   Updated: 2019/02/26 18:04:26 by bleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "./libft.h"
# include <stdarg.h>

typedef struct			s_var
{
	char				*string;
	char				*argtoapp;
	char				*attribut;
	char				*flags;
	int					count;
	long long			width;
	long long			precision;
	long long			conver;
	long long			nblong;
	long double			nbdouble;
	unsigned long long	unsignedll;
	char				*s;
}						t_var;

int						ft_printf(const char *restrict format, ...);
int						init_arg(const char *format, t_var *arg);
void					init_vars(t_var *arg);
int						ft_read(const char *format, int i, t_var *arg,
																	va_list ap);
int						ft_str(int start, int end, const char *format,
																	t_var *arg);
int						ft_last_conv(t_var *arg, const char *format, int end);
int						ft_parser(const char *format, int end, t_var *arg);
int						ft_option(const char *format, int end, t_var *arg);
int						ft_width(const char *format, int start, t_var *arg);
int						ft_precision(const char *format, int start, t_var *arg);
int						ft_flags(const char *format, int start, t_var *arg);
int						ft_conversions(t_var *arg, va_list ap);
void					ft_getva_arg(t_var *arg, va_list ap);
void					ft_conv_flags(t_var *arg);
void					ft_conv_flags2(t_var *arg, int i);
int						ft_tostr(t_var *arg);
int						ft_toitoa(t_var *arg);
int						ft_adress(t_var *arg);
int						ft_tocs(t_var *arg);
char					*ft_append(char *str, char c);
int						ft_tof(t_var *arg);
int						ft_togetu(t_var *arg);
char					*ft_arrondi_entiers(t_var *arg, char *entiers,
																char *decis);
char					*ft_decimales_18(t_var *arg, long long sub,
															long double copy);
char					*ft_entiers_18(long double copy);
char					*ft_arrondi_decimales(t_var *arg, char *str);
int						ft_options(t_var *arg);
int						ft_hashtag(t_var *arg);
int						ft_go_minus(t_var *arg);
int						ft_go_width(t_var *arg);
char					*ft_append_first(char w, char *str);
int						ft_width_neg(t_var *arg, char w);
int						ft_add_precision(t_var *arg);
int						ft_add_width(t_var *arg);
int						ft_space(t_var *arg);
int						ft_width_minus(t_var *arg);
int						ft_check_space(t_var *arg);
int						ft_precision_neg(t_var *arg);
int						ft_check_0(t_var *arg);
int						ft_restart(t_var *arg);
void					ft_free_for_all(t_var *arg);
int						ft_conversions(t_var *arg, va_list ap);
void					ft_conv_int(t_var *arg, va_list ap);
void					ft_conv_unsigned(t_var *arg, va_list ap);
void					ft_conv_float(t_var *arg, va_list ap);
int						ft_hashtag_x(t_var *arg);
int						ft_check_zero(t_var *arg);
int						ft_width_0(t_var *arg);
int						ft_conv_c(t_var *arg, va_list ap);
void					ft_flags_c(t_var *arg);
int						ft_exceptions(t_var *arg);
int						ft_check_hashtag(t_var *arg);
int						ft_precision_p(t_var *arg);
int						ft_goto_cs(t_var *arg, va_list ap);
int						ft_width_neg_bis(t_var *arg, char w, int i);

#endif
