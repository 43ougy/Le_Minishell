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
				ret[i] = malloc(sizeof(char) * ver - j - 1);
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
		}
		while (args[j] == ' ' && args[j])
			j++;
		if (!ret)
			return (NULL);
	}
	i = -1;
	j = 0;
	while (++i < nb_args)
	{
		if (args[j] == '"')
		{
			w = 0;
			ver = j + 1;
			while (args[ver] != '"' && args[ver])
				ver++;
			if (args[ver] == '"')
			{
				j++;
				while (args[j] != '"')
				{
					ret[i][w] = args[j];
					w++;
					j++;
				}
			}
			j = ver + 1;
		}
		else
		{
			w = 0;
			while (args[j] != ' ' && args[j] != '"' && args[j])
			{
				ret[i][w] = args[j];
				w++;
				j++;
			}
		}
		while (args[j] == ' ' && args[j])
			j++;
		ret[i][w] = '\0';
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

char **split_args(char *args)
{
	char	**ret;
	int		nb_args;

	//printf("%s\n", args);
	nb_args = number_of_args(args);
	ret = malloc(sizeof(char *) * nb_args);
	if (!ret)
		return (NULL);
	ret = get_args(args, nb_args, ret);
	if (!ret)
	{
		printf("Renvoie NULL\n");
		return (NULL);
	}
	//printf("%d\n", nb_args);
	return (ret);
}

int	main()
{
	int		i = -1;
	char	**test = split_args("ech \"[  t ]\"   \"  \"");
	for (int i = 0; test[i]; i++)
	{
		printf("%s\n", test[i]);
	}
	//test = split_args("echo -n \"test1     tset2\" autretest \"\" \" \"");
	while (test[++i])
		free(test[i]);
	free(test);
	return (0);
}
