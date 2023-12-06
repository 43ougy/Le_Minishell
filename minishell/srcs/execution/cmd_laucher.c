#include "execution.h"

void	_cmd_laucher(t_parse *parse, t_prompt *data)
{
	t_red	red;
	int		fd_in;
	int		*fd_out;
	int		status;

	fd_out = out_red(red);
	fd_in = in_red(red);
	status = _execute(parse, data, fd_in, fd_out[0]);
	//why write data in fd_out ? if dup2 in execute
	//else write outfile if fd_out != stdout
	//why fd_in > 2?
	//destroy .tmp file
	return (status);
}