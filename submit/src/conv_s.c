/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 22:38:43 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 16:01:35 by yijhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	precision_s(char **str, t_spec *spec)
{
	char	*new;
	int		i;

	if (spec->precision == -1)
		return ;
	if (ft_strlen(*str) > (size_t)spec->precision)
	{
		new = (char *)ft_memalloc(spec->precision + 1);
		i = 0;
		while (i < spec->precision)
		{
			new[i] = (*str)[i];
			i++;
		}
		free(*str);
		*str = new;
	}
}

char	*width_s_2(int pad_len, char *padding, char c)
{
	int		i;

	i = 0;
	while (i < pad_len)
	{
		padding[i] = c;
		i++;
	}
	return (padding);
}

void	width_s(char **str, t_spec *spec)
{
	int		len;
	char	*padding;
	char	*newstr;
	int		pad_len;

	if (spec->width == -1 || spec->width <= (len = ft_strlen(*str)))
		return ;
	pad_len = spec->width - len;
	padding = (char *)ft_memalloc(pad_len + 1);
	if (spec->flags['-'])
		newstr = ft_strjoin(*str, width_s_2(pad_len, padding, ' '));
	else if (spec->flags['0'])
		newstr = ft_strjoin(width_s_2(pad_len, padding, '0'), *str);
	else
		newstr = ft_strjoin(width_s_2(pad_len, padding, ' '), *str);
	free(padding);
	free(*str);
	*str = newstr;
}

int		conv_s(va_list *ap, t_spec *spec)
{
	char	*str;
	int		len;

	if ((str = va_arg(*ap, char *)))
		str = ft_strdup(str);
	else
		str = ft_strdup("(null)");
	precision_s(&str, spec);
	width_s(&str, spec);
	len = ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (len);
}
