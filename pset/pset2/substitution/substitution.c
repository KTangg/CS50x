#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{

    //Check for key
    if (argc == 2)
    {

        if (strlen(argv[1]) == 26)
        {
            //checking for key precision
            for (int i = 0; i < 26; i++)
            {
                if (isalpha(argv[1][i]))
                {
                    //checking duplicate
                    for (int j = i + 1; j < 26; j++)
                    {
                        if (toupper(argv[1][i]) == toupper(argv[1][j]))
                        {
                            printf("Duplicate Key\n");
                            return 1;
                        }
                    }
                }
                else
                {
                    printf("Only alphabet allow\n");
                    return 1;
                }

            }
            //Create Ascii for alphabet
            //int alphabets[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83 ,84, 85 , 86, 87, 88, 89, 90};
            //Set up for encrypt code
            //Create Encrypt Array
            char encrypt[26];
            for (int i = 0; i < 26; i++)
            {
                encrypt[i] = toupper(argv[1][i]);
            }

            //Receive Secret Message
            string plain = get_string("plaintext: ");

            //Encrypting
            printf("ciphertext: ");
            for (int i = 0, A = 65; i < strlen(plain); i++)
            {

                if (isalpha(plain[i]))
                {
                    if (isupper(plain[i]))
                    {
                        int index = toupper(plain[i]) - A;
                        printf("%c", encrypt[index]);
                    }
                    else
                    {
                        int index = toupper(plain[i]) - A;
                        printf("%c", tolower(encrypt[index]));
                    }
                }
                else
                {
                    printf("%c", plain[i]);
                }
            }
            printf("\n");
            return 0;

        }
        //Invalid
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}