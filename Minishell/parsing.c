#include "ra_shell.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	get_nb_args(char *input)
{
	int	i;
	int	ret;
	int	j;

	i = 0;
	ret = 0;
	while (input[i])
	{
		if (!is_white_space(input[i]) && input[i] != 39 && input[i] != 34 && input[i])//39 = ' & 34 = "
		{
			ret++;
			while (!is_white_space(input[i]) && input[i] != 39 && input[i] != 34 && input[i])
				i++;
		}
		while (is_white_space(input[i]) && input[i] != 39 && input[i] != 34 && input[i])
			i++;
		if (input[i] == 39 || input[i] == 34)
		{
			j = i;
			i++;
			if (input[j] == 39)
			{
				while (input[i] != 39 && input[i])
					i++;
			}
			else if (input[j] == 34)
			{
				while (input[i] != 34 && input[i])
					i++;
			}
			if (i - j > 1 && (input[i] == 34 || input[i] == 39))
				ret++;
			else if (input[i] != 34 && input[i] != 39)
			{
				write(1, "Bad argument value\n", 19);
				return (-1);
			}
			i++;
		}
	}
	return (ret);
}

char	**get_args(char **ret, char *input, int nb_args)//attribution des arguments dans un double tableau
{
	int		i;
	int		j;
	int		ch;
	int		ar;

	i = -1;
	ch = 0;
	j = 0;
	while (++i < nb_args)
	{
		ar = 0;
		if (!is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
		{
			while (!is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
			{
				ch++;
				ar++;
			}
			ret[i] = malloc(sizeof(char) * ar + 1);
			ret[i] = ft_strncpy(ret[i], input + ch - ar, ar);
			ret[i][ar] = '\0';
		}
		else if (input[ch] == 39 || input[ch] == 34)
		{
			j = ch;
			ch++;
			if (input[j] == 39)
			{
				while (input[ch] != 39 && input[ch])
				{
					ch++;
					ar++;
				}
			}
			else if (input[j] == 34)
			{
				while (input[ch] != 34 && input[ch])
				{
					ch++;
					ar++;
				}
			}
			ret[i] = malloc(sizeof(char) * ar + 1);
			ret[i] = ft_strncpy(ret[i], input + ch - ar, ar);
			ret[i][ar] = '\0';
			ch++;
		}
		if (!ret[i])
			return (NULL);
		while (is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
			ch++;
	}
	return (ret);
}

char	**check_args(char *input)//check args from the stdin (data->prompt)
{
	int		nb_args;
	char	**args;

	args = NULL;
	nb_args = get_nb_args(input);
	args = malloc(sizeof(char *) * nb_args + 1);
	if (!args)
		return (NULL);
	args = get_args(args, input, nb_args);
	return (args);
}

int	main()
{
	char	**args = check_args("test arg 'fhuwfuie     fjwie'   autres arguments\n");
	int		i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}
