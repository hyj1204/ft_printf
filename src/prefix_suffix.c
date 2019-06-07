/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_suffix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yijhuang <yijhuang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 02:26:05 by yijhuang          #+#    #+#             */
/*   Updated: 2019/06/07 02:26:09 by yijhuang         ###   ########.fr       */
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
	if ((spec->flags['o'] || spec->flags['O']) && spec->flags['#'] && str[0][0] != '0')
		prefix("0", str);
	//如果字符串的第一个字符不是0，并且有#标示+要转换成8进制的话，就在字符串之前加上0
}

void		prefix_sign(char **str, t_spec *spec)
{
	if (spec->isunsigned) //如果输入是unsigned的话
	{
		if (spec->flags['#'] && spec->flags['x'] && !(spec->iszero))
			prefix("0x", str);
		if (spec->flags['#'] && spec->flags['X'] && !(spec->iszero))
			prefix("0X", str);
		return ;
	}
	if (!spec->ispos)  //ispos = 0 的话，说明是负数，负数在之前加负号
		prefix("-", str);
	else if (spec->flags['+']) //如果有+标示的话，遇到正数在正数之前加+号
		prefix("+", str);
	else if (spec->flags[' ']) //如果有空格标示的话，遇到正数在正数之前加空格
		prefix(" ", str);
}
