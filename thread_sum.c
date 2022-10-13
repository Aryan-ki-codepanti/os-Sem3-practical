#include <pthread.h>
#include <stdio.h>

int sum;

void *calc_sum(void *arg)
{
    int i, n = atoi(arg);
    sum = 0;
    for (i = 0; i <= n; i++)
        sum += i;
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Inappropriate arguments\n");
        return -1;
    }

    if (atoi(argv[1]) < 0)
    {
        printf("Invalid argument entered\n");
        return -1;
    }

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, calc_sum, argv[1]);
    pthread_join(tid, NULL);

    printf("Sum of %s numbers : %d\n", argv[1], sum);
    return 0;
}