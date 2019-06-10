/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:26:05 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/08 19:01:28 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void		prefix(char *pre, char **str)
{
	char	*new;

	new = ft_strjoin(pre, *str);
	free(*str);
	*str = new;
}

void		suffix(char **str, char *post)
{
	char	*new;

	new = ft_strjoin(*str, post);
	free(*str);
	*str = new;
}

void		prefix_octal(char **str, t_spec *spec)
{
	if ((spec->flags['o'] || spec->flags['O']) \
	&& spec->flags['#'] && str[0][0] != '0')
		prefix("0", str);
}

void		prefix_sign(char **str, t_spec *spec)
{
	if (spec->isunsigned)
	{
		if (spec->flags['#'] && spec->flags['x'] && !(spec->iszero))
			prefix("0x", str);
		if (spec->flags['#'] && spec->flags['X'] && !(spec->iszero))
			prefix("0X", str);
		return ;
	}
	if (!spec->ispos)
		prefix("-", str);
	else if (spec->flags['+'])
		prefix("+", str);
	else if (spec->flags[' '])
		prefix(" ", str);
}
