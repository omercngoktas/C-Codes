#include <stdio.h>

int rec(int n)
{
    if(n == 1)
        return 2;

    else
    {
        return rec(n/5) + n;
    }
        
    
}

int main()
{
    printf("%d", rec(625));
    return 0;
}