/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 21:46:13 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/03 16:47:34 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void md5_print_prompt(t_md5_flags flags, const char *s, t_bool is_string)
{
	if (flags.q || flags.r || !s)
		return ;
	if (is_string)
		ft_printf("MD5 (\"%s\") = ", s);
	else
		ft_printf("MD5 (%s) = ", s);
}

static void md5_print_final(t_md5_flags flags, unsigned char sum[16], const char *s, t_bool is_string)
{
	md5_print_prompt(flags, s, is_string);
	md5_put_sum(sum);
	if (flags.r && !flags.q && s && is_string)
		ft_printf(" \"%s\"", s);
	else if(flags.r && !flags.q && s)
		ft_printf(" %s", s);
	ft_putchar('\n');	
}

void	md5_print_string(t_md5_flags flags, unsigned char sum[16], const char *s)
{
	md5_print_final(flags, sum, s, True);
}

void	md5_print(t_md5_flags flags, unsigned char sum[16], const char *s)
{
	md5_print_final(flags, sum, s, False);
}

void	md5_put_sum(unsigned char sum[16])
{
	int		i;

	i = 0;
	while(i < 16)
	{
		ft_printf("%02x", sum[i]);
		i++;
	}
}