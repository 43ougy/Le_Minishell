#include "execution.h"

static int	*init_fdout(t_red *red, int len, int *i)
{
	
}

int	*out_red(t_red *red)
{
//_tblen to get tab len of red->output
//if files > 1 create a .tmp file to copy data to all files.
//return (int *tab) of all fd (stdout and files)

	int	len;
	int	*ret;

	len = _tblen(red->output1) + _tblen(red->output2);
	ret = init_fdout(red, len);
}