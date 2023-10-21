# Le_Minishell
## 42 Project

The goal is to re-create a little shell.

### Dependencies
none
```shell
make #or make re
./minishell #no argument required
```
I use this function to find the "PATH" in the "char **env"
```C
//I use a structure where I put the **env data to modify it as I want
//It will be usefull later with the code of unset/export builtin
char	*ft_getenv(char **env, char *path_name)
{
	int		li;
	int		ch;
	char	*path;

	li = 0;
	path = NULL;
	while (env[li])
	{
		ch = 0;
		while (env[li][ch] && env[li][ch] != '=')
			ch++;
		path = ft_substr(env[li], 0, ch);
		if (ft_strcomp(path_name, path))
		{
			free(path);
			path = NULL;
			path = ft_strdup(env[li] + ch + 1);
			break ;
		}
		free(path);
		path = NULL;
		li++;
	}
	return (path);
}
//All functions in this code (except free()) are re-coded
//so you can find them and modify them as you want
```
## Implementation

#### BUILTIN
```
echo
cd
pwd
export
unset
env
exit
```

#### PIPE

#### SIGNAL
```
CTRL -C
CTRL -D
CTRL -\
```
#### REDIRECTION (WIP)
