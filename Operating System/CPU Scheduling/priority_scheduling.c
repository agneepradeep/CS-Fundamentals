#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completion_time;
    int turn_around_time;
    int waiting_time;
} typedef Process;

// Function prototypes
void preemptive_priority_scheduling(int, Process[]);
void print_statistics(int, Process[]);

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process process_array[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time, burst time, and priority for Process %d: ", i + 1);
        scanf("%d %d %d", &process_array[i].arrival_time, &process_array[i].burst_time, &process_array[i].priority);
        process_array[i].process_id = i + 1;
        process_array[i].remaining_time = process_array[i].burst_time;
        process_array[i].completion_time = 0;
        process_array[i].turn_around_time = 0;
        process_array[i].waiting_time = 0;
    }

    preemptive_priority_scheduling(n, process_array);
    return 0;
}

void preemptive_priority_scheduling(int n, Process process_array[])
{
    int time = 0, completed = 0, current_process = -1;
    int minimum_priority = INT_MAX;
    bool is_process_running = false;

    printf("\nExecution Order: ");

    while (completed < n)
    {
        // Find the process with the highest priority available at the current time
        for (int i = 0; i < n; i++)
        {
            if (process_array[i].arrival_time <= time && process_array[i].remaining_time > 0 && process_array[i].priority < minimum_priority)
            {
                minimum_priority = process_array[i].priority;
                current_process = i;
                is_process_running = true;
            }
        }

        if (!is_process_running)
        {
            time++;
            continue;
        }

        printf("P%d ", process_array[current_process].process_id);
        process_array[current_process].remaining_time--;
        time++;
        minimum_priority = process_array[current_process].priority;

        // Check if the process is completed
        if (process_array[current_process].remaining_time == 0)
        {
            process_array[current_process].completion_time = time;
            process_array[current_process].turn_around_time =
                process_array[current_process].completion_time - process_array[current_process].arrival_time;
            process_array[current_process].waiting_time =
                process_array[current_process].turn_around_time - process_array[current_process].burst_time;

            completed++;
            minimum_priority = INT_MAX;
            is_process_running = false;
        }
    }

    printf("\n\nPreemptive Priority Scheduling Results\n");
    print_statistics(n, process_array);
}

void print_statistics(int n, Process process_array[])
{
    float total_turnaround_time = 0, total_waiting_time = 0;

    printf("+------------+--------------+------------+-----------------+-----------------+---------------+\n");
    printf("| Process ID | Arrival Time | Burst Time | Completion Time | Turn Around Time | Waiting Time |\n");
    printf("+------------+--------------+------------+-----------------+-----------------+---------------+\n");
    
    for (int i = 0; i < n; i++) {
        printf("| %*d | %*d | %*d | %*d | %*d | %*d |\n",
               strlen("Process ID"), process_array[i].process_id, 
               strlen("Arrival Time"), process_array[i].arrival_time,
               strlen("Burst Time"), process_array[i].burst_time, 
               strlen("Completion Time"), process_array[i].completion_time,
               strlen("Turn Around Time"), process_array[i].turn_around_time,
               strlen("Waiting Time"), process_array[i].waiting_time);
        
        total_turnaround_time += process_array[i].turn_around_time;
        total_waiting_time += process_array[i].waiting_time;
    }

    printf("+------------+--------------+------------+----------+-----------------+-----------------+---------------+\n");
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
}
