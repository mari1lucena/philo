#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!parse_args(argc, argv, &table))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (table.stop_now)
		return (0);
	if (!init_table(&table))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (!start_simulation(&table))
	{
		write(2, "Error\n", 6);
		clean_table(&table);
		return (1);
	}
	clean_table(&table);
	return (0);
}
