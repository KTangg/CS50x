#include <stdio.h>
#include <cs50.h>

long get_card(void);
long power(long x, long a);
int checking(long card, int digith);


int main(void)
{
    //Asking Card Number
    long card = get_card();

    //Branching to 4 Conditions (Visa(1), Amex, Visa(2), Master)

    // Master Card Checking 15,16 digith is (51,52,53,54,55)
    if (card / power(10, 14)  >= 51 && (card / power(10, 14)) <= 55)
    {
        int digith = 16;

        int x;
        x = checking(card, digith);

        if (x == 1)
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    // Visa(Cond. 1) 16 digith is 4
    else if ((card / power(10, 15)) == 4)
    {
        int digith = 16;

        int x;
        x = checking(card, digith);

        if (x == 1)
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }

    }

    // Amex 15,14 digith is (34,37)
    else if (card / power(10, 13) == 34 || card / power(10, 13) == 37)
    {
        int digith = 15;

        int x;
        x = checking(card, digith);

        if (x == 1)
        {
            printf("AMEX\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    // Visa(Cond. 2) 13 digith is 4
    else if (card / power(10, 12) == 4)
    {
        int digith = 13;

        int x;
        x = checking(card, digith);

        if (x == 1)
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    // Not on Any Condition is Invalid
    else
    {
        printf("INVALID\n");
    }


}




long get_card(void)
{
    //Asking for Card Number(Positive Number only)
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n <= 0);
    return n;
}


//Power Function
long power(long x, long a)
{
    //Doing Mathematic Power Operation
    // power(x,a) = x^a
    long y = 1;
    for (long i = 0; i < a; i++)
    {
        y = y * x;
    }
    return y;
}


//Checking Validate Funtion
int checking(long card, int digith)
{

    //This for Other Number that *2
    int other_sum = 0;

    for (int i = 2; i <= digith; i += 2)
    {
        //Finding Other Number
        int other = (card % power(10, i) / power(10, i - 1));

        //Multiply its by 2
        int other_2 = other * 2;

        //Sum its digit product
        int digit_p = (other_2 / 10) + (other_2 % 10);

        //Sum  of Other digit product
        other_sum += digit_p;

    }

    //This for the rest that not *2

    int rest_sum = 0;

    for (int j = 1; j <= digith; j += 2)
    {
        //Finding the rest
        int rest_n = (card % power(10, j) / power(10, j - 1));

        //Summing it
        rest_sum += rest_n;
    }

    //Sum all product

    int sum = other_sum + rest_sum;

    //Checking last digit
    int x;

    if (sum % 10 == 0)
    {
        x = 1;
    }

    else
    {
        x = 0;
    }

    return x;
}
