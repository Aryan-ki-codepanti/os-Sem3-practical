#include <stdio.h>

float average(int arr[], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += arr[i];
    return (float)(s) / n;
}

int main()
{
    printf("FCFS ALGO\n");
    int n;

    printf("Enter number of processes\n");
    scanf("%d", &n);

    int processes[n];
    int burst_times[n];
    int wait[n];
    int turn_around[n];

    printf("Enter the processes\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processes[i]);

    printf("Enter the burst times\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &burst_times[i]);

    wait[0] = 0;

    for (int i = 1; i < n; i++)
        wait[i] = wait[i - 1] + burst_times[i - 1];

    for (int i = 0; i < n; i++)
        turn_around[i] = wait[i] + burst_times[i];

    printf("--------SUMMARY-------------\n");
    printf("Process\tBurst\tWait\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", processes[i], burst_times[i], wait[i], turn_around[i]);

    float avg_wait = average(wait, n);
    float avg_turnaround = average(turn_around, n);

    printf("Average wait time : %.2fs\n", avg_wait);
    printf("Average turnaround time : %.2fs\n", avg_turnaround);

    return 0;
}