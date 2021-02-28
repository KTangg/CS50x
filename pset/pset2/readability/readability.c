#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int count_letter(string text);
int count_word(string text);
int count_sentence(string text);
float word100(int word);

int main(void)
{
    //Getting text input
    string text = get_string("Text: ");

    //Count letter and show
    int letters;

    letters = count_letter(text);
    //printf("%i letter(s)\n", letters);

    //Count word and show
    int words;

    words = count_word(text);
    //printf("%i word(s)\n", words);

    //Count sentence and show
    int sentences;

    sentences = count_sentence(text);
    //printf("%i sentence(s)\n", sentences);


    // Index calculation
    float L;
    float S;
    float factor = word100(words);


    L = letters * factor;
    S = sentences * factor;

    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    //Condition before rounding number
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else if (round(index) >= 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}



int count_letter(string text)
{

    int letter = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Checking is it alphabet or not if yes count
        if (isalpha(text[i]))
        {
            //printf("This is a letter: ");
            //printf("%c\n", text[i]);
            letter += 1;
        }
    }

    return letter;
}

int count_word(string text)
{

    int word = 0;

    //Checking for spacebar
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Checking is it alphabet or not if yes count
        if (text[i] == ' ')
        {
            word += 1;
        }
    }
    //Plus one for ending
    return word + 1;
}

int count_sentence(string text)
{
    int sentence = 0;

    //Checking for . ? !
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //Checking for . ? !
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence += 1;
        }
    }
    return sentence;
}

float word100(int word)
{
    //factor to find average for 100 words
    float factor = 100.0 / word;
    return factor;
}


