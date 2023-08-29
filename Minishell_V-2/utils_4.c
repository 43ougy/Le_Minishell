#include "ra_shell.h"

//separer les arguments
//checker les quotes
//checker les arguments

//OPTI LES FONCTIONS ET CORRIGER LES BUGS

char	**get_args(char *args, int nb_args, char **ret)
{
	int	i;
	int	j;
	int	w;
	int	ver;

	i = -1;
	j = 0;
	ver = 0;
	while (++i < nb_args)
	{
		w = 0;
		if (args[j] == '"')
		{
			ver = j + 1;
			while (args[ver] != '"' && args[ver])
				ver++;
			if (args[ver] == '"')
			{
				if (ver - j - 1 > 0)
				{
					ret[i] = malloc(sizeof(char) * (ver - j - 1) + 1);
					ret[i] = ft_strncpy(ret[i], args + j + 1, ver - j - 1);
					ret[i][ver - j - 1] = '\0';
				}
				else
					printf("Espace alloue negatif ou egal a zero\n");
			}
			else
			{
				ret[i] = malloc(1);
				ret[0] = '\0';
			}
			j = ver + 1;
		}
		else
		{
			while (args[j] != ' ' && args[j] != '"' && args[j])
			{
				w++;
				j++;
			}
			ret[i] = malloc(sizeof(char) * w + 1);
			ret[i] = ft_strncpy(ret[i], args + j - w, w);
			ret[i][w] = '\0';
		}
		while (args[j] == ' ' && args[j])
			j++;
		if (!ret[i])
			return (NULL);
	}
	return (ret);
}

int	number_of_args(char *args)
{
	int	i;
	int	nb_args;
	int	j;

	i = 0;
	nb_args = 0;
	j = 0;
	while (args[i])
	{
		if (args[i] != ' ' && args[i] != '"')
		{
			nb_args++;
			while (args[i] != ' ' && args[i] != '"' && args[i])
				i++;
		}
		if (args[i] == '"')
		{
			j = i + 1;
			while (args[j] != '"' && args[j])
				j++;
			if (args[j] == '"')
			{
				if (j - i > 1)
					nb_args++;
			}
			i = j + 1;
		}
		while (args[i] == ' ' && args[i])
				i++;
	}
	return (nb_args);
}

char	**split_args(char *args)
{
	char	**ret;
	int		nb_args;

	//printf("%s\n", args);
	nb_args = number_of_args(args);
	ret = malloc(sizeof(char *) * (nb_args + 1));
	ret[nb_args] = '\0';
	if (!ret)
		return (NULL);
	ret = get_args(args, nb_args, ret);
	//printf("%d\n", nb_args);
	return (ret);
}
/*
int	main()
{
	int		i = 0;
	char	**test = split_args("ech \"[  t ]\"   \"  \"");
	//test = split_args("echo -n \"test1     tset2\" autretest \"\" \" \"");
	while (test[i])
	{
		printf("%s\n", test[i]);
		free(test[i]);
		i++;
//	printf("test\n");
	}
	free(test);
	return (0);
}*/
