#include <stdio.h>
#include <cs50.h>


int get_h(void);
void blocking(int h);

int main(void)
{
    int h;
    //Getting H
    h = get_h();

    //Create ##
    blocking(h);
}








int get_h(void)
{
    //Keep Asking For 0<h<9
    int number;
    do
    {
        //Asking User
        number = get_int("Height: ");

    }
    //Checking
    while (number < 1 || number > 8);
    return number;
}

void blocking(h)
{
    //Construct ## base on h outer for height inner for width
    for (int i = 1; i <= h; i++)
    {
        //Left Side Spacing before#
        for (int j = h; j >= 1; j--)
        {

            if (j > i)
            {
                printf(" ");
            }

            else
            {
                printf("#");
            }


        }

        printf("  ");

        //Righ Side Just do #
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        //Start new Line
        printf("\n");

    }
}