#include <cs50.h>
#include <stdio.h>

int get_start_int(void);
int get_end_int(int start);


int main(void)
{
    // TODO: Prompt for start size

    int start;
    start = get_start_int();

    // TODO: Prompt for end size

    int end;
    end = get_end_int(start);

    // TODO: Calculate number of years until we reach threshold

    int llama;
    int n = 0;
    llama = start;

    while (llama < end)
    {
        int born = llama/3;
        int pass = llama/4;

        llama = llama+born-pass;


        n++;
    }

    // TODO: Print number of years

    printf("Years: %i\n",n);
}



int get_start_int(void)
{

    int i;

    do
    {
        i = get_int("Start size: ");

    }

    while (i < 9);
    return i;
}



int get_end_int(start)
{
    int i;

    do
    {
        i = get_int("End size: ");

    }

    while (i <= start);
    return i;
}