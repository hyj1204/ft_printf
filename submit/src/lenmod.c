/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:55 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 17:09:48 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

long long			len_mod(va_list *ap, t_spec *spec)
{
	long long			num;

	if (spec->flags['l'] == 2)
		num = va_arg(*ap, long long);
	else if (spec->flags['l'] == 1)
		num = va_arg(*ap, long);
	else if (spec->flags['h'] == 2)
		num = (signed char)va_arg(*ap, int);
	else if (spec->flags['h'] == 1)
		num = (short)va_arg(*ap, int);
	else
		num = va_arg(*ap, int);
	return (num);
}

unsigned long long	lenmod_unsigned(va_list *ap, t_spec *spec)
{
	unsigned long long	num;

	if (spec->flags['l'] == 2)
		num = va_arg(*ap, unsigned long long);
	else if (spec->flags['l'] == 1)
		num = va_arg(*ap, unsigned long);
	else if (spec->flags['h'] == 2)
		num = (unsigned char)va_arg(*ap, unsigned int);
	else if (spec->flags['h'] == 1)
		num = (unsigned short)va_arg(*ap, unsigned int);
	else
		num = va_arg(*ap, unsigned int);
	return (num);
}
