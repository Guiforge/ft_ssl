/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 21:46:13 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/12 14:48:43 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void	sha256_print_prompt(t_sha256_flags flags, const char *s, t_bool is_string)
{
	if (flags.q || flags.r || !s)
		return ;
	if (is_string)
		ft_printf("SHA256 (\"%s\") = ", s);
	else
		ft_printf("SHA256 (%s) = ", s);
}

static void	sha256_print_final(t_sha256_flags flags, unsigned char sum[32],
												const char *s, t_bool is_string)
{
	sha256_print_prompt(flags, s, is_string);
	sha256_put_sum(sum);
	if (flags.r && !flags.q && s && is_string)
		ft_printf(" \"%s\"", s);
	else if (flags.r && !flags.q && s)
		ft_printf(" %s", s);
	ft_putchar('\n');
}

void		sha256_print_string(t_sha256_flags flags, unsigned char sum[32],
																const char *s)
{
	sha256_print_final(flags, sum, s, True);
}

void		sha256_print(t_sha256_flags flags, unsigned char sum[32], const char *s)
{
	sha256_print_final(flags, sum, s, False);
}

void		sha256_put_sum(unsigned char sum[32])
{
	int		i;

	i = 0;
	while (i < 32)
	{
		ft_printf("%02x", sum[i]);
		i++;
	}
}
