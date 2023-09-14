#include <stdbool.h>
#include "libmath.h"

bool	is_near_zero(float n)
{
	return (n == 0 || (0 < n && n < EPSILON) || (- EPSILON < n && n < 0));
}
