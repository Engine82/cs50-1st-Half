#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    //check if there is only one string in argv (argc = 2)
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //check if only digits are input into argv[1]
    if (!only_digits(argv[1]))
    {
        printf("Usage ./caesar key\n");
        return 1;
    }

    //convert argv1 to int, get plaintext, rotate plaintext into cyphertext, print cyphertext.
    int cypher = atoi(argv[1]);
    string plaintext = get_string("plaintext:  ");

    //print title of output
    printf("ciphertext: ");

    //go charactar by charactar, coverting to cyphertext
    for (int j = 0; j < strlen(plaintext); j++)
    {
        char cyphertext = rotate(plaintext[j], cypher);
        printf("%c", cyphertext);
    }
    //print new line
    printf("\n");
    return 0;
}

//digit testing function
bool only_digits(string s)
{
    int i = 0;
    do
    {
        //if digits, continue testing
        if (isdigit(s[i]))
        {
            i++;
        }

        //if not digit, return
        else
        {
            return false;
        }
    }
    while (i < strlen(s));
    return true;
}

//charactar rotation function
char rotate(char c, int n)
{
    //rotate if lowercase
    if (islower(c))
    {
        c = ((c - 97 + n) % 26) + 97;
        return c;
    }
    //rotate if uppercase
    else if (isupper(c))
    {
        c = ((c - 65 + n) % 26) + 65;
        return c;
    }

    //return the original value if not a letter
    else
    {
        return c;
    }
}