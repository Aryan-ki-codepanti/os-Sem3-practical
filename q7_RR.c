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

int get_next_process(int current_process_idx, int time_counter, int processes[], int arrival[], int burst[], int n)
{

    int process_num;
    do
    {
        current_process_idx = (current_process_idx + 1) % n;
        process_num = processes[current_process_idx];
    } while (!(arrival[process_num] <= time_counter && burst[process_num] > 0));
    return current_process_idx;
}

void update_waiting(int current_process, int time_counter, int current_time_used, int wait[], int arrival[], int burst[], int n)
{
    for (int process = 0; process < n; process++)
    {
        if (process == current_process)
            continue;
        // else
        if ((arrival[process] < time_counter) && (burst[process] > 0))
        {
            // if (wait[process] == 0)
            //     wait[process] = time_counter - arrival[process];
            // else
            wait[process] += min(current_time_used, time_counter - arrival[process]);
        }
    }
}

int main()
{

    int n, q;
    printf("Enter number of processes and time quantum\n");
    scanf("%d %d", &n, &q);

    int processes[n];
    int burst[n];
    int burst_copy[n];
    int arrival[n];
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
    }

    // initialise wait to 0 for all
    for (int i = 0; i < n; i++)
        wait[i] = 0;

    int time_counter = array_min(arrival, n), final_time = array_min(arrival, n) + array_sum(burst, n);

    int current_process_idx = 0, current_process = processes[0];
    int current_time_used = min(q, burst[current_process]);

    time_counter += current_time_used;
    burst[current_process] -= current_time_used;
    update_waiting(current_process, time_counter, current_time_used, wait, arrival, burst, n);

    while (time_counter < final_time)
    {

        // schedule next process
        current_process_idx = get_next_process(current_process_idx, time_counter, processes, arrival, burst, n);
        current_process = processes[current_process_idx];

        current_time_used = min(q, burst[current_process]);
        time_counter += current_time_used;
        burst[current_process] -= current_time_used;

        update_waiting(current_process, time_counter, current_time_used, wait, arrival, burst, n);
    }

    // calculate turnaround
    for (int process = 0; process < n; process++)
        turnaround[process] = wait[process] + burst_copy[process];

    printf("------------------------------------------\n");
    printf("Process\tArrival\tBurst\tWait\tTurnaround\n");
    for (int process = 0; process < n; process++)
        printf("%d\t%d\t%d\t%d\t%d\n", process, arrival[process], burst_copy[process], wait[process], turnaround[process]);

    float avg_wait = (float)(array_sum(wait, n)) / n;
    float avg_turnaround = (float)(array_sum(turnaround, n)) / n;

    printf("Average waiting time : %.2f\n", avg_wait);
    printf("Average turnaround time : %.2f\n", avg_turnaround);

    return 0;
}