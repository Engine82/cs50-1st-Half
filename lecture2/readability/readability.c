#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int final = round(index);

    if (final < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final >= 1 && final < 16)
    {
        printf("Grade %i\n", final);
    }
    else if (final >= 16)
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int charactars = strlen(text);
    int letters = 0;
    for (int i = 0; i < charactars; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

int count_words(string text)
{
    int charactars = strlen(text);
    int words = 1;
    for (int i = 0; i <= charactars; i++)
    {
        if (isspace(text[i]))
        {
            words += 1;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int charactars = strlen(text);
    int sentences = 0;
    for (int i = 0; i <= charactars; i++)
    {
        if (text[i] == '.')
        {
            sentences += 1;
        }
        else if (text[i] == '?')
        {
            sentences += 1;
        }
        else if (text[i] == '!')
        {
            sentences += 1;
        }
    }
    return sentences;
}