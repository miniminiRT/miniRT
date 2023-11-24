#include "miniRT.h"

void	file_name_check(char *f_name)
{
	if (f_name[ft_strlen(f_name) - 1] != 't'
		|| f_name[ft_strlen(f_name) - 2] != 'r'
		|| f_name[ft_strlen(f_name) - 3] != '.')
	{
		error();
		exit(1);
	}
}

int	arr_size(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

int	count_dot(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
