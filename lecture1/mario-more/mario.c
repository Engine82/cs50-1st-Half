#include <cs50.h>
#include <stdio.h>

void print_blocks(int i);

int main(void)
{
    //make rows and coumns of # based on user input
    //ask user how big?  -  do while loops for size parameters
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //create each lineof text, adding one # each side until reaches specification  -  loop
    //print spaces (number -i), then # (i), 2 spaces, # (i), then \n

    //print blocks until mass reaches "hightxhight" in size
    for (int i = 0; i < height; i++)
    {
        //print spaces
        //one space per hight - i
        for (int spaces = 0; spaces < height - i - 1; spaces++)
        {
            printf(" ");
        }

        //print blocks
        print_blocks(i);

        //print 2 spaces
        printf("  ");

        //print blocks
        print_blocks(i);

        //start new line
        printf("\n");
    }
}

//Block printing function
//no return value, name, recieves variable i, an int;
void print_blocks(int i)
{
    //print i number of blocks - increases +1 each cycle, until specified number "hight" are printed.
    for (int blocks = 0; blocks < i + 1; blocks++)
    {
        printf("#");
    }
}
