#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    // create initial pointer to point to the first number
    node *list = NULL;

    // iterate through all command line arguments
    for (int i = 1; i < argc; i++)
    {
        // Why atoi? I still dont get it
        int number = atoi(argv[i]);

        // malloc one node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        // assign the number section of node n the command line argument currently stored in the "number" variable
        n->number = number;
        n->next = NULL;

        n->next = list;
        list = n;
    }
}
