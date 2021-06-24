#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"

static char	*compare(struct dirent *dp, char *command, char *bin)
{
	char	*bin_command;

	bin_command = NULL;
	if (ft_strcmp(dp->d_name, command) == 0)
	{
		bin_command = ft_strjoin(bin, command);
		if (bin_command != NULL)
			return (bin_command);
	}
	return (NULL);
}

static char	*cucle_read(DIR *dir, struct dirent **dp, char *command, char *bin)
{
	char	*bin_command;

	*dp = readdir(dir);
	if (*dp == NULL)
	{
		closedir(dir);
		return (NULL);
	}
	bin_command = compare(*dp, command, bin);
	if (bin_command != NULL)
	{
		closedir(dir);
		return (bin_command);
	}
	return (NULL);
}

static char	*get_bin(char *command, char *path)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*bin_command;

	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	bin_command = cucle_read(dir, &dp, command, path);
	if (bin_command != NULL)
		return (bin_command);
	while (dp != NULL)
	{
		bin_command = cucle_read(dir, &dp, command, path);
		if (bin_command != NULL)
			return (bin_command);
	}
	return (NULL);
}

static char	*chek_executable(char *command)
{
	struct stat	st;
	char	*bin_command;
	int	out;

	bin_command = NULL;
	out = stat(command, &st);
	if (out == 0 && st.st_mode & S_IXUSR)
	{
		bin_command = ft_strdup(command);
		return (bin_command);
	}
	return (bin_command);
}

char	*search_bin(char *command)
{
	char	*bin_command;

	bin_command = chek_executable(command);
	if (bin_command != NULL)
		return (bin_command);
	bin_command = get_bin(command, "/Users/skitsch/.brew/bin/");
	if (bin_command != NULL)
		return (bin_command);
	bin_command = get_bin(command, "/usr/local/bin/");
	if (bin_command != NULL)
		return (bin_command);
	bin_command = get_bin(command, "/usr/bin/");
	if (bin_command != NULL)
		return (bin_command);
	bin_command = get_bin(command, "/bin/");
	if (bin_command != NULL)
		return (bin_command);
	bin_command = get_bin(command, "/usr/sbin/");
	if (bin_command != NULL)
		return (bin_command);
	bin_command = get_bin(command, "/sbin/");
	if (bin_command != NULL)
		return (bin_command);
	bin_command = get_bin(command, "/usr/local/munki/");
	if (bin_command != NULL)
		return (bin_command);
	return (NULL);
}
