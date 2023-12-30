#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    //Loop for each CHAR of string
    //   i is loop counter, n is string length
    string message = get_string("Message: ");

    for (int i = 0, n = strlen(message); i < n; i++)
    {
        //1. isolate charactar
        int decimal = message[i];

        int binary[] = {0, 0, 0, 0, 0, 0, 0, 0};

        int j = 0;
        //2. convert ASCII into binary
        while (decimal > 0)
        {
            binary[j] = decimal % 2;
            decimal = decimal / 2;
            j++;
        }

        //3. Print binary as bulbs
        for (int k = BITS_IN_BYTE - 1; k >= 0; k--)
        {
            print_bulb(binary[k]);
        }
        //new line at end of charactar
        printf("\n");
    }

}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
