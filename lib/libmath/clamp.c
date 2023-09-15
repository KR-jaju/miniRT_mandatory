float	clamp(float a, float min, float max)
{
	if (a > max)
		return (max);
	else if (a < min)
		return (min);
	else
		return (a);
}
