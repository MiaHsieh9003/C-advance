#include "space.h"

tTypeScore score_buf[N]; //preallocated memory space

void get_score_space(tTypeScore **pp_score)
{
    **pp_score = score_buf[((*pp_score)->loc)];
	printf("     get_score_space(): giving space numbered %d\n", (*pp_score)->loc);
    return;
}

void return_score_space (int loc)
{
    printf("     return_score_space(): return space numbered %d\n", loc);
}
