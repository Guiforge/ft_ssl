/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 11:31:43 by gpouyat           #+#    #+#             */
/*   Updated: 2019/02/01 12:08:14 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static t_ssl_hash	g_hashes[] = {
	{"md5", &md5},
	{"sha256", &sha256},
	{"sha512", &sha512},
	{"sha384", &sha384},
	{"sha224", &sha224},
	{NULL, NULL},
};

static int			help_full(const char *cmd)
{
	if (!cmd)
		return (1);
	ft_printf("ft_ssl:Error: '%s' is an invalid command.\n", cmd);
	ft_putendl("Message Digest commands\n"
"md5               sha256            sha512\n"
"sha224            sha384\n"
"Cipher commands");
	return (1);
}

static t_ssl_hash	get_hash(const char *hash)
{
	int			i;

	i = -1;
	if (!hash)
		return ((t_ssl_hash){NULL, NULL});
	while (g_hashes[++i].buff != NULL)
		if (!ft_strncmp(g_hashes[i].buff, hash, ft_strlen(g_hashes[i].buff)))
			break ;
	return (g_hashes[i]);
}

static t_ssl_hash	read_prompt(char **line)
{
	int			ret;
	t_ssl_hash	hash;

	ft_putstr("ft_ssl>");
	while ((ret = get_next_line(STDIN_FILENO, line)) && ret != -1)
	{
		hash = get_hash(*line);
		if (hash.buff)
			break ;
		if (*line && **line)
			help_full(*line);
		ft_putstr("ft_ssl>");
	}
	return (hash);
}

int					handle_stdin(void)
{
	char		*cmd;
	t_ssl_hash	hash;
	char		**av;
	int			ret;

	hash = read_prompt(&cmd);
	av = ft_strsplit(cmd, ' ');
	if (!cmd || !av)
		log_fatal("Malloc Error!");
	if (hash.buff && av)
		ret = hash.f(ft_strdbllen((const char **)av), (const char **)av);
	else
		help_full(cmd);
	free(cmd);
	ft_strdblfree(av);
	return (-1);
}

int					main(int ac, const char **argv)
{
	t_ssl_hash	hash;

	if (INTERN_DEBUG_FT_SSL)
		log_init(".log", 2);
	if (ac <= 1)
		return (handle_stdin());
	hash = get_hash(argv[1]);
	if (hash.buff)
		return (hash.f(--ac, ++argv));
	help_full(argv[1]);
	return (-1);
}
