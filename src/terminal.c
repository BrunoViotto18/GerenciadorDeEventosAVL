#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

void clear_terminal(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait_for_enter(void)
{
    printf("Pression Enter para continuar...");
    fflush(stdout);

    while (true)
    {
        int c = getchar();

        if (c == '\n' || c == EOF)
        {
            return;
        }
    }
}
