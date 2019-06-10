/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:23:29 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 17:10:38 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			conv_f(va_list *ap, t_spec *spec)
{
	int			len;
	char		*str;

	if (spec->flags['L'])
		lftos(va_arg(*ap, long double), &str, spec);
	else
		ftos(va_arg(*ap, double), &str, spec);
	width_d(&str, spec);
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}
