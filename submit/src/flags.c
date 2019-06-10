/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 20:52:05 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 15:29:39 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		get_width_precision(const char *restrict *format, \
int *width, int *precision)
{
	int	num;
	int	more;

	num = 0;
	more = 0;
	while (ft_isdigit(**format))
	{
		num = num * 10 + (**format - '0');
		(*format)++;
	}
	if (num && (*width = num))
		more = 1;
	if (**format == '.')
	{
		(*format)++;
		num = 0;
		while (ft_isdigit(**format))
		{
			num = num * 10 + (**format - '0');
			(*format)++;
		}
		*precision = num;
		more = 1;
	}
	return (more);
}

char	is_flag(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	return (0);
}

int		get_flags(const char *restrict *format, char *flags)
{
	int		more;

	more = 0;
	while (is_flag(**format))
	{
		more = 1;
		flags[(int)**format] = 1;
		*format = *format + 1;
	}
	return (more);
}

int		print_a_arg(const char *restrict *format, va_list *ap, \
int (*dispatch[])(), t_spec *spec)
{
	char	conv;
	int		more;

	if (**format == '%')
	{
		ft_putchar(*(*format)++);
		return (1);
	}
	more = 1;
	while (more)
	{
		more = 0;
		more += get_flags(format, spec->flags);
		more += get_width_precision(format, &spec->width, &spec->precision);
		more += get_len_modifier(format, spec->flags);
	}
	if ((conv = get_conv_spec(format, spec->flags)) == 0)
	{
		if (**format)
			return (conv_single(spec, *(*format)++));
		return (0);
	}
	return (dispatch[(int)conv](ap, spec));
}
