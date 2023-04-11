#include <stdio.h>

/*****************************************************************/
// 3.5
void decode1(long *xp, long *yp, long *zp){
    long a = *xp;
    long b = *yp;
    long c = *zp;
    *yp = a;
    *zp = b;
    *xp = c;
}
/*****************************************************************/

int main()
{


    return 0;
}