#include <stdio.h>
//include library with get_string
#include <cs50.h>

//in a future lecture
int main(void)
{
    //ask user for their name. And stop forgetting the semicolons *sigh*
    string name = get_string("What's your name friend?: ");

    //display "hello, *user's name*"
    printf("hello, %s\n", name);
}