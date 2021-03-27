#include <stdio.h>

int main()
{
    int n = 0;
    int i, j, count = 0;
    for(i = 0; i <= n; i++)
    {
        for(j = 0; j <= i; j++)
        {
            count++;
        }
    }
    printf("count: %d\n", count);
    

    return 0;
}