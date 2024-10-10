#include "philo.h"

int	check_args(int argc, char **argv)
{
	int		i;
	long	value;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 0);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (printf("Error: Invalid argument: %s\n", argv[i]), 0);
		value = ft_atol(argv[i]);
		if (value <= 0 || value > LONG_MAX)
			return (printf("Error: Invalid argument value: %s\n", argv[i]), 0);
		i++;
	}
	if (ft_atol(argv[1]) > 200)
		return (printf("Error: Invalid number of philosophers (max 200)\n"), 0);
	return (1);
}


int	main(int argc, char **argv)
{
    t_data data;
	if (!check_args(argc, argv))
		return (1);
    if(!init_data(&data, argc, argv))
    { 
        printf("Error: Initialization failed\n");
        // need some cleanup function here
        return (1);
    }
    start_simulation(&data);
    //cleanup;
    return (0);
}
