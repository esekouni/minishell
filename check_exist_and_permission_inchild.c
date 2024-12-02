/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exist_and_permission_inchild.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:24:10 by aouchaad          #+#    #+#             */
/*   Updated: 2023/06/23 15:09:33 by aouchaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_fromf_case(char *file)
{
	int	cread;
	int	fd;
	int	exist;

	exist = access(file, F_OK);
	if (exist == -1)
	{
		print_error(file, strerror(errno));
		exit (1);
	}
	else
	{
		cread = access(file, R_OK);
		if (cread == -1)
		{
			print_error(file, strerror(errno));
			exit (1);
		}
	}
	fd = open(file, O_RDONLY, 0777);
	return (fd);
}

static int	file_not_exist(char *file, int type, int fd)
{
	if (file[0] == '\0')
	{
		print_error(file, "No such file or directory");
		exit (1);
	}
	if (type == write_inf)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
		fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0777);
	return (fd);
}

static int	write_inf_and_append_case(char *file, int type, int fd, int exist)
{
	int	cwrite;

	exist = access(file, F_OK);
	if (exist == -1)
		return (file_not_exist(file, type, fd));
	else
	{
		cwrite = access(file, W_OK);
		if (cwrite == -1)
		{
			print_error(file, strerror(errno));
			exit (1);
		}
	}
	if (type == write_inf)
		fd = open(file, O_RDWR | O_TRUNC, 0777);
	else
		fd = open(file, O_RDWR | O_APPEND, 0777);
	return (fd);
}

int	check_exist_and_permission_inchild(char *file, int type)
{
	int	fd;
	int	exist;

	fd = -2;
	exist = -2;
	if (type == read_fromf)
		return (read_fromf_case(file));
	else if (type == write_inf || type == append)
		return (write_inf_and_append_case(file, type, fd, exist));
	return (-1);
}
