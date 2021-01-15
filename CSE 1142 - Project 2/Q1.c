// Omercan Goktas 150119671
// The purpose of the program is replacing the position of the number that user wants to change.

#include <stdio.h>
#include <stdlib.h>

void reserveN(int *number, int N)
{
    char number_list[100];
    int number2 = *number, x = 0; // number2 refers to *number and x is going to be sort of number from end to beginning.
    int b, z = 0; // z is going to be the number that is sort of number from beginning to end.
    char v;
    while(number2 != 0) // this while loop helps to sort number from ends to beginning.
    {
        x = x * 10;
        x = x + number2 % 10;
        number2 = number2 / 10;
    }
    sprintf(number_list, "%d", x);
    v = number_list[N-1];
    number_list[N-1] = number_list[0];
    number_list[0] = v;
    sscanf(number_list, "%d", &b);
    while(b != 0)
    {
        z = z * 10;
        z = z + b % 10;
        b = b / 10;
    }
    printf("Your reserved number: %d", z);
}

int main()
{
    int N, number, lenght = 1, number2;
    printf("Please enter an integer: ");
    scanf("%d", &number);
    if (number <= 0)
    {
        printf("Please enter a valid integer.\n");
        return;
    }
    else
    {
        number2 = number;
        printf("Please enter an integer for the reserve number: ");
        scanf("%d", &N);
        if (N <=0)
        {
            printf("Please enter a valid integer.");
            return;
        }
        else
        {
            while(number >= 10)
            {
                number = number/10;
                lenght += 1;
            }
            number = number2;
            if (lenght <= N-1)
            {
                printf("N must be less than %d!", lenght+1);
                return;
            }
            else
            {
                reserveN(&number, N);
            }
        }
    }


    return 0;
}
