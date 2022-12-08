#include <stdio.h>

struct Hole
{
    int capacity;
    int isOccupied;
} typedef Hole;

int isAvailable(Hole arr[], int n)
{
    for (int i = 0; i < n; i++)
        if (!arr[i].isOccupied)
            return 1;
    return 0;
}

int first_fit(Hole arr[], int n)
{
    for (int i = 0; i < n; i++)
        if (!arr[i].isOccupied)
            return i;
    return -1;
}

int best_fit(Hole arr[], int n)
{
    int best = -1;
    int smallest = __INT_MAX__;
    for (int i = 0; i < n; i++)
        if (!arr[i].isOccupied && arr[i].capacity < smallest)
        {
            smallest = arr[i].capacity;
            best = i;
        }
    return best;
}

int worst_fit(Hole arr[], int n)
{
    int worst = -1;
    int biggest = -__INT_MAX__ - 1;
    for (int i = 0; i < n; i++)
        if (!arr[i].isOccupied && arr[i].capacity > biggest)
        {
            biggest = arr[i].capacity;
            worst = i;
        }
    return worst;
}

int main()
{
    int size;

    printf("Enter number of memory holes : ");
    scanf("%d", &size);

    printf("Enter size of n memory holes in bytes\n");

    Hole memory[size];
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &memory[i].capacity);
        memory[i].isOccupied = 0;
    }

    int choice, hole;
    while (1)
    {
        printf("--------MENU------\n");
        printf("1.Allocate a hole with FIRST FIT\n");
        printf("2.Allocate a hole with BEST FIT\n");
        printf("3.Allocate a hole with WORST FIT\n");
        printf("4.Exit\n");
        printf("Make a choice\n");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting program\n");
            break;
        }
        if (!isAvailable(memory, size))
        {
            printf("Ran out of memory\n");
            break;
        }

        switch (choice)
        {
        case 1:
            hole = first_fit(memory, size);
            break;

        case 2:
            hole = best_fit(memory, size);
            break;
        case 3:
            hole = worst_fit(memory, size);
            break;
        }

        memory[hole].isOccupied = 1;
        printf("Hole %d of %d bytes is now allocated\n", hole, memory[hole].capacity);
    }

    return 0;
}