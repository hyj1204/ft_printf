/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:25:05 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 17:34:33 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

long	power(int base, int exp)
{
	int		i;
	long	result;

	i = 1;
	if (exp == 0)
		return (0);
	result = base;
	while (i < exp)
	{
		result *= base;
		i++;
	}
	return (result);
}

void	itoa_snip(char **str, int i, long long val)
{
	while (i)
	{
		(*str)[--i] = val % 10 + '0';
		val /= 10;
	}
}

int		fractional(char **str, long long fract, t_spec *spec)
{
	int			i;
	int			overflow;
	int			len;

	overflow = 0;
	i = spec->precision;
	len = d_len(fract);
	*str = (char *)ft_memalloc(sizeof(char) * (i + 1));
	if ((fract % 10) > 4)
		fract += 10;
	if (len < d_len(fract))
		overflow = 1;
	fract /= 10;
	itoa_snip(str, i, fract);
	return (overflow);
}

void	lftos(long double num, char **str, t_spec *spec)
{
	long long	whole;
	long long	fract;
	int			i;
	char		*new;
	char		*combined;

	if (!(num >= 0 && (spec->ispos = 1)))
		num = -num;
	i = 0;
	if (spec->precision == -1)
		spec->precision = 6;
	whole = (long long)num;
	num -= whole;
	fract = (long long)(power(10, spec->precision + 1) * num);
	whole += fractional(str, fract, spec);
	if (spec->precision || spec->flags['#'])
		prefix(".", str);
	i = d_len(whole);
	new = (char *)ft_memalloc(sizeof(char) * (i + 1));
	itoa_snip(&new, i, whole);
	combined = ft_strjoin(new, *str);
	free(*str);
	free(new);
	*str = combined;
}

void	ftos(double num, char **str, t_spec *spec)
{
	long long	whole;
	long long	fract;
	int			i;
	char		*new;
	char		*combined;

	i = 0;
	if (!(num >= 0 && (spec->ispos = 1)))
		num = -num;
	if (spec->precision == -1)
		spec->precision = 6;
	whole = (long long)num;
	num -= whole;
	fract = (long long)(power(10, spec->precision + 1) * num);
	whole += fractional(str, fract, spec);
	if (spec->precision || spec->flags['#'])
		prefix(".", str);
	i = d_len(whole);
	new = (char *)ft_memalloc(sizeof(char) * (i + 1));
	itoa_snip(&new, i, whole);
	combined = ft_strjoin(new, *str);
	free(*str);
	free(new);
	*str = combined;
}
