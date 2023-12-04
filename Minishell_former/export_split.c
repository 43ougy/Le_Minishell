/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:03:26 by abougy            #+#    #+#             */
/*   Updated: 2023/12/01 16:13:23 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_comp_name(t_prompt *data, t_run *run, char *name)
{
	int	len;
	int	i;

	i = -1;
	while (data->set_env[++i])
	{
		len = 0;
		while (data->set_env[i][len] && data->set_env[i][len] != '=')
			len++;
		run->comp = ft_substr(data->set_env[i], 0, len);
		if (ft_strcomp(name, run->comp))
		{
			free(run->comp);
			run->comp = ft_strdup(data->set_env[i]);
			run->i = -1;
			break ;
		}
		free(run->comp);
	}
}

void	_comp_env(t_prompt *data, t_run *run, char *name)
{
	int	i;
	int	len;

	i = -1;
	run->i = 0;
	while (data->d_env[++i])
	{
		len = 0;
		while (data->d_env[i][len] && data->d_env[i][len] != '=')
			len++;
		run->equal = ft_substr(data->d_env[i], 0, len);
		if (ft_strcomp(name, run->equal))
		{
			free(run->equal);
			free(data->d_env[i]);
			data->d_env[i] = ft_strdup(run->comp);
			free(run->comp);
			run->i = -1;
			break ;
		}
		free(run->equal);
	}
}

void	_env_len(t_prompt *data, t_run *run)
{
	run->len = 0;
	while (data->d_env[run->len])
		run->len++;
	run->len++;
}

char	**_set_export_env(t_prompt *data, t_run *run, char **new_env)
{
	int	i;

	i = -1;
	while (data->d_env[++i])
		new_env[i] = ft_strdup(data->d_env[i]);
	new_env[i] = ft_strdup(run->comp);
	new_env[run->len] = NULL;
	i = -1;
	while (data->d_env[++i])
		free(data->d_env[i]);
	free(data->d_env);
	data->d_env = NULL;
	free(run->comp);
	return (new_env);
}
/*
char	**run_export(t_prompt *data, char *name)
{
	t_run	run;
	char	**new_env;

	new_env = NULL;
	run.i = 0;
	if (data->set_env)
	{
		_comp_name(data, &run, name);
		if (run.i != -1)
			return (data->d_env);
	}
	else
		return (data->d_env);
	if (data->d_env)
	{
		_comp_env(data, &run, name);
		if (run.i == -1)
			return (data->d_env);
	}
	_env_len(data, &run);
	new_env = malloc(sizeof(char *) * (run.len + 1));
	if (!new_env)
		return (NULL);
	new_env = _set_export_env(data, &run, new_env);
	return (new_env);
}*/

char	**_new_env(t_prompt *data)
{
	char	**new_env;
	int		i;
	int		len;
	
	i = -1;
	len = 0;
	while (data->d_env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 1));
	while (data->d_env[++i])
		new_env[i] = ft_strdup(data->d_env[i]);
	new_env[i] = NULL;
	return (new_env);
}

char	**_sort_new_env(char **new_env)
{
	int		i;
	int		j;
	char	*tmp;
	
	i = -1;
	while (new_env[++i])
	{
		j = -1;
		while (new_env[++j + 1])
		{
			if (_comp(new_env[i], new_env[j]) < 0)
			{
				tmp = new_env[i];
				new_env[i] = new_env[j];
				new_env[j] = tmp;
			}
		}
	}
	return (new_env);
}

void	_sort_env(t_prompt *data)
{
	char	**new_env;
	int		i;

	i = -1;
	if (!data->d_env)
		return ;
	new_env = _new_env(data);
	if (!new_env)
		return ;
	new_env = _sort_new_env(new_env);
	while (new_env[++i])
	{
		write(1, "declare -x ", 11);
		write(1, new_env[i], ft_strlen(new_env[i]));
		write(1, "\n", 1);
		free(new_env[i]);
	}
	free(new_env);
}

char	**run_export(t_prompt *data, char *name)
{
	t_run	run;
	char	**new_env;
	int		j;

	new_env = NULL;
	run.comp = NULL;
	run.i = 0;
	j = 0;
	if (!name)
	{
		_sort_env(data);
		return (data->d_env);
	}
	else if (data->equals)
	{
		while (name[j] != '=')
			j++;
		run.name = ft_substr(name, 0, j);
		if (data->set_env)
		{
			_comp_name(data, &run, run.name);
			if (run.i == -1)
			{
				free(run.comp);
				run.comp = ft_strdup(name);
			}
		}
		if (data->d_env)
		{
			if (!run.comp)
				run.comp = ft_strdup(name);
			_comp_env(data, &run, run.name);
			if (run.i == -1)
			{
				free(run.name);
				return (data->d_env);
			}
		}
		_env_len(data, &run);
		new_env = malloc(sizeof(char *) * (run.len + 1));
		if (!new_env)
			return (NULL);
		if (!run.comp)
			run.comp = ft_strdup(name);
		new_env = _set_export_env(data, &run, new_env);
		free(run.name);
	}
	else
	{
		if (data->set_env)
		{
			_comp_name(data, &run, name);
			if (run.i != -1)
				return (data->d_env);
		}
		else
			return (data->d_env);
		if (data->d_env)
		{
			_comp_env(data, &run, name);
			if (run.i == -1)
				return (data->d_env);
		}
		_env_len(data, &run);
		new_env = malloc(sizeof(char *) * (run.len + 1));
		if (!new_env)
			return (NULL);
		new_env = _set_export_env(data, &run, new_env);
	}
	return (new_env);
}
//checker data->equals sur name et set data->set_env avec la variable envoyer
//ensuite exporte la commande

/*
pour test=valeur
--si test est dans env, remplacer valeur de test dans env
ex (PATH=valeur, dans env --> PATH=valeur "ancienne valeur contenant tout les paths")
--sinon test n'est pas dans l'env mais est stoquer de sorte a l'utiliser
ex (test=valeur, dans env --> [...] mais echo $test --> print valeur

pour export
--si simple
print env trier en ASCII
--sinon avec test=valeur en argument
exporter test dans l'env avec le meme comportement qu'au dessus
--sinon avec test
si test est stoque l'exporter sinon ne rien faire
*/
