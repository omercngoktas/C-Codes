// Omercan Goktas 150119671
// With this program, user inputs a size of letter and then user inputs a letter, after that this letter shown on screen and user will be asked if user wants to continue printing letters.

#include <stdio.h>
#include <stdlib.h>

char ch;

void wW(int size)
{
    int i, x = 3, size2 = size*2-3, v = 0, m, a, z = 0;
    while(x > 0) // this loop prints highest line.
    {
        printf("*");
        for (i = 0; i < size2; i++) // this loop gives blanks between top of the stars.
        {
            printf(" ");
        }
        x--;
    }
    printf("\n");
    for (i = 0; i < size - 2; i++) // this loop works for middle lines.
    {
        v++; // this determines how many blanks( ) will be there from the beginning.
        for (m = 0; m < v; m++) // this loop gives blanks( ) from the beginning.
        {
            printf(" ");
        }
        size2 -= 2;
        a = 2;
        while (a > 0)
        {
            z++;
            printf("*");
            for (m = 0; m < size2; m++) // this loop gives blanks between stars.
            {
                printf(" ");
            }
            printf("*");
            for (m = 0; m < z; m++) // this loop gives blanks at the end of the line.
            {
                printf(" ");
            }
            a--;
        }
        printf("\n");
    }

    // here is about bottom of the line.
    size2 = size*2-3;
    for (i = 0; i < size - 1; i++)
    {
        printf(" ");
    }
    printf("*");
    for (i = 0; i < size2; i++)
    {
        printf(" ");
    }
    printf("*");
}

void xX(int size)
{
    int i, m = 0, x, v, size2 = size, lenght_of_char, size3 = 1, lenght_of_char2;
    lenght_of_char = (size - 1) / 2;
    for(i = 0; i < size; i++) // this loop prints stars(*) from up until it reaches middle of X.
    {
        if(lenght_of_char == 0) // this 'if loop' checks if middle of the x is done.
        {
            printf("*\n");
            break;
        }
        size2 -= 2; // this determines blanks value between stars(*).
        printf("*"); // this prints first star(*).
        for(x = 0; x < size2; x++) // this loop prints blank( ) between stars(*).
        {
            printf(" ");
        }
        printf("*\n"); // this prints ending star and pass one line.
        m++; // this adds 1 to m.
        for(v = 0; v < m; v++) // this loop prints blank( ) from beginning.
        {
            printf(" ");
        }
        lenght_of_char--; // this reduces lenght_of_char 1 value.
    }

    lenght_of_char2 = (size - 1) / 2;
    for(i = 0; i < size; i++) // this loop prints stars(*) from middle of X until it reaches to down.
    {
        if (lenght_of_char2 == 0) // this loop checks if stars(*) reaches the down.
        {
            break;
        }
        m--;
        for(v = 0; v < m; v++) // this loop give blanks from the beginning.
        {
            printf(" ");
        }

        printf("*"); // this prints star(*) at the beginning.
        for(x = 0; x < size3; x++) // this loop gives blanks( ) between stars(*).
        {
            printf(" ");
        }
        size3 += 2; // this helps for loop to gives blanks( ) between starts(*).
        printf("*\n"); // this prints star(*) at the end of the line.
        lenght_of_char2--; // this reduces lenght_of_char2 1 value.
    }
}

void yY(int size)
{
    int size2 = (size - 1) / 2;
    int i, x, v, m = 0;
    for(i = 0; i < size2; i++) // this loop works according to size of double stars which are in a line.
    {
        printf("*"); // this prints first star of the line.
        for(x = 0; x < size - 2; x++) // this line gives blanks between two stars.
        {
            printf(" ");
        }
        size -= 2;
        printf("*\n"); // this prints second star of the line.
        m++;
        for(v = 0; v < m; v++) // this loop gives blanks from the beginning to place first star of the line.
        {
            printf(" ");
        }
    }
    for(i = 0; i < size2 + 1; i++) // this loop prints single star which are in a line.
    {
        printf("*\n"); // this prints star.
        for(x = 0; x < m; x++)
        {
            printf(" "); // this gives blanks from the beginning.
        }
    }
}

void zZ(int size)
{
    int lenght = 0, size2 = size, i, x;
    for(i = 0; i < size; i++) // this prints highest stars(*) of the beginning.
    {
        printf("*");
    }
    printf("\n"); // this gives a blank( ) from highest line.
    while(lenght+1 < size) // this loop determines how many lines there will be.
    {
        for(x = 1; x < size2; x++) // this loop give blanks from the beginning.
        {
            printf(" ");

        }
        printf("*\n"); // this prints star(*) at the end of the line.
        lenght++;
        size2--;
    }
    for (i = 0; i < size; i++) // this loop prints stars of the bottom line.
    {
        printf("*");
    }
}

void function()
{
    int size, i = 1;
    char letter, yes_no;
    printf("Enter the size: ");
    scanf("%d", &size);
    while(i = 1)
    {
        if(size %2 == 0)
        {
            printf("Invalid size. Enter the size again: ");
            scanf("%d", &size);
            continue;
        }
        else if ((size <= 3)) // if the size equals or lesser than 3, it prints an error and takes input again.
        {
            printf("Invalid size. Enter the size again: ");
            scanf("%d", &size);
            continue;
        }
        else
        {
            break;
        }
    }
    printf("Enter the letter: ");
    scanf(" %c", &letter);
    while(i = 1)
    {
        if (letter == 'w' || letter == 'W')
        {
            wW(size);
            break;
        }
        else if (letter == 'x' || letter == 'X')
        {
            xX(size);
            break;
        }
        else if (letter == 'y' || letter == 'Y')
        {
            yY(size);
            break;
        }
        else if (letter == 'z' || letter == 'Z')
        {
            zZ(size);
            break;
        }
        else
        {
            printf("Invalid letter. Enter the letter again: ");
            scanf(" %c", &letter);
            continue;
        }
    }
    while(i = 1)
    {
        char yes_no;
        printf("\nWould you like to continue? (Y or N): ");
        scanf(" %c", &yes_no);

        switch(yes_no)
        {
        case 'n':
            printf("Goodbye :)");
            break;
        case 'N':
            printf("Goodbye :)");
            break;
        case 'y':
            function();
            break;
        case 'Y':
            function();
            break;
        default:
            printf("Invalid input.");
            continue;
        }
        return;
    }
}

int main()
{

    printf("Welcome to the letter printer.\n");
    function();
    return 0;
}
