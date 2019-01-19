/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 21:46:13 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/19 18:52:11 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void	sha512_print_prompt(t_sha512_flags flags, const char *s, t_bool is_string)
{
	if (flags.q || flags.r || !s)
		return ;
	if (is_string)
		ft_printf("SHA512 (\"%s\") = ", s);
	else
		ft_printf("SHA512 (%s) = ", s);
}

static void	sha512_print_final(t_sha512_flags flags, unsigned char sum[64],
												const char *s, t_bool is_string)
{
	sha512_print_prompt(flags, s, is_string);
	sha512_put_sum(sum);
	if (flags.r && !flags.q && s && is_string)
		ft_printf(" \"%s\"", s);
	else if (flags.r && !flags.q && s)
		ft_printf(" %s", s);
	ft_putchar('\n');
}

void		sha512_print_string(t_sha512_flags flags, unsigned char sum[64],
																const char *s)
{
	sha512_print_final(flags, sum, s, True);
}

void		sha512_print(t_sha512_flags flags, unsigned char sum[64], const char *s)
{
	sha512_print_final(flags, sum, s, False);
}

void		sha512_put_sum(unsigned char sum[64])
{
	int		i;

	i = 0;
	while (i < 64)
	{
		ft_printf("%02x", sum[i]);
		i++;
	}
}
