#include <stdio.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int array_sum(int arr[], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += arr[i];
    return s;
}

int array_min(int arr[], int n)
{
    int min_element = arr[0];
    for (int i = 0; i < n; i++)
        min_element = min(min_element, arr[i]);
    return min_element;
}

int process_with_non_zero_burst(int burst[], int n)
{
    for (int process = 0; process < n; process++)
    {
        if (burst[process] > 0)
            return process;
    }
    return -1;
}

int get_next_higher_priority(int time_counter, int arrival[], int burst[], int priority[], int n)
{

    int max_prior = process_with_non_zero_burst(burst, n); // let it
    for (int process = 0; process < n; process++)
    {
        if (burst[process] != 0 && arrival[process] <= time_counter && priority[process] < priority[max_prior])
            max_prior = process;
    }
    return max_prior;
}

void update_waiting(int current_process, int time_counter, int current_time_used, int wait[], int arrival[], int burst[], int n)
{
    for (int process = 0; process < n; process++)
    {
        if (process == current_process)
            continue;

        if ((arrival[process] < time_counter) && (burst[process] > 0))
            wait[process] += current_time_used;
    }
}

int main()
{
    int n;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    int processes[n];
    int arrival[n];
    int priority[n];
    int burst[n];
    int burst_copy[n];
    int wait[n];
    int turnaround[n];

    int process_tmp, burst_tmp;
    for (int i = 0; i < n; i++)
    {
        printf("Enter a process number %d : ", i);
        scanf("%d", &process_tmp);
        processes[i] = process_tmp;
        printf("Enter arrival time : ");
        scanf("%d", &arrival[process_tmp]);
        printf("Enter burst time : ");
        scanf("%d", &burst_tmp);
        burst[process_tmp] = burst_tmp;
        burst_copy[process_tmp] = burst_tmp;
        printf("Enter priority : ");
        scanf("%d", &priority[process_tmp]);
    }

    // initialise wait to 0 for all
    for (int i = 0; i < n; i++)
        wait[i] = 0;

    int time_counter = array_min(arrival, n);
    int final_time = time_counter + array_sum(burst, n);

    int current_process, current_time_used;

    while (time_counter < final_time)
    {
        current_process = get_next_higher_priority(time_counter, arrival, burst, priority, n);
        current_time_used = 1;
        time_counter += current_time_used;
        burst[current_process] -= 1; // task completed
        update_waiting(current_process, time_counter, current_time_used, wait, arrival, burst, n);
    }

    // calculate turnaround
    for (int process = 0; process < n; process++)
        turnaround[process] = wait[process] + burst_copy[process];

    printf("------------------------------------------\n");
    printf("Process\tArrival\tBurst\tPriority\tWait\tTurnaround\n");
    for (int process = 0; process < n; process++)
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", process, arrival[process], burst_copy[process], priority[process], wait[process], turnaround[process]);

    float avg_wait = (float)(array_sum(wait, n)) / n;
    float avg_turnaround = (float)(array_sum(turnaround, n)) / n;

    printf("Average waiting time : %.2f\n", avg_wait);
    printf("Average turnaround time : %.2f\n", avg_turnaround);

    return 0;
}