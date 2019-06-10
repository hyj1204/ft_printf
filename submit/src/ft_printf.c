/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 18:12:12 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 15:16:29 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	init_dispatch(int (*dispatch[])())
{
	dispatch['s'] = conv_s;
	dispatch['c'] = conv_c;
	dispatch['p'] = conv_p;
	dispatch['d'] = conv_d;
	dispatch['i'] = conv_d;
	dispatch['u'] = conv_u;
	dispatch['o'] = conv_o;
	dispatch['x'] = conv_x;
	dispatch['X'] = conv_x;
	dispatch['f'] = conv_f;
	dispatch['F'] = conv_f;
}

void	init_spec(t_spec *spec)
{
	spec->width = -1;
	spec->precision = -1;
	spec->isnull = 0;
	spec->iszero = 0;
	spec->ispos = 0;
	spec->isunsigned = 0;
	ft_bzero(spec->flags, 128);
}

int		helper(va_list *ap, const char *restrict format)
{
	int		(*dispatch[128])(va_list *ap, t_spec *spec);
	int		num_printed;
	int		num;
	t_spec	spec;

	num = 0;
	spec.flags = (char *)ft_memalloc(sizeof(char) * 128);
	init_dispatch(dispatch);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			init_spec(&spec);
			num_printed = print_a_arg(&format, ap, dispatch, &spec);
			num += num_printed;
		}
		else
		{
			ft_putchar(*format++);
			num++;
		}
	}
	free(spec.flags);
	return (num);
}

int		ft_printf(const char *format, ...)
{
	int		num_chars_printed;
	va_list	ap;

	va_start(ap, format);
	num_chars_printed = helper(&ap, format);
	va_end(ap);
	return (num_chars_printed);
}
