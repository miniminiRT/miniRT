#include "../miniRT.h"

int	get_root(t_util *util, t_hit_record *rec)
{
	(void)rec;
	util->discriminant = (util->b * util->b) - 4 * util->a * util->c;
	if (util->discriminant < 0)
		return (0);
	util->sqrtd = sqrt(util->discriminant);
    util->root = (-util->b - util->sqrtd) / (2 * util->a);
	// util->root1 = (-util->b + util->sqrtd) / (2 * util->a);
	// if (util->root > util->root1)
	// 	util->root = util->root1;
	if (util->root < rec->tmin || util->root > rec->tmax)
	{
		util->root = (-util->b + util->sqrtd) / (2 * util->a);
		if (util->root < rec->tmin || util->root > rec->tmax)
			return (0);
	}
	return (1);
}
