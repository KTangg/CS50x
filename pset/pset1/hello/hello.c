#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Getting User Name
    string name = get_string("Your Name: ");
    
    // Display Hello, User
    printf("hello, %s\n", name);
    
}