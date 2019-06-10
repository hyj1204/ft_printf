/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:24:12 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 17:13:28 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int			conv_u(va_list *ap, t_spec *spec)
{
	int			len;
	char		*str;
	long long	num;

	spec->isunsigned = 1;
	num = lenmod_unsigned(ap, spec);
	if (num == 0)
		spec->iszero = 1;
	itoa_u(num, &str);
	precision_d(&str, spec);
	width_d(&str, spec);
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}
