#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

struct process_block {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
} typedef process;

void shortest_job_first_scheduling (int, process []);
bool check_process_left (int, process []);
int fetch_shortest_process (int, process []);
void print_statistics (int, process [], int []);

int time_counter = 0;

int main () {
    int n;
    printf("Type no. of Processes: ");
    scanf("%d",&n);
    
    process process_array[n];
    int arrival_time[n];
    int burst_time[n];
    
    printf("Type processes arrival time: ");
    for (int i = 0; i<n; i++) {
        scanf("%d",&arrival_time[i]);
    }
    
    printf("Type processes burst time: ");
    for (int i = 0; i<n; i++) {
        scanf("%d",&burst_time[i]);
    }
    
    for (int i = 0; i<n; i++) {
        process_array[i].process_id = i;
        process_array[i].arrival_time = arrival_time[i];
        process_array[i].burst_time = burst_time[i];
        process_array[i].completion_time = -1;
        process_array[i].turn_around_time = -1;
        process_array[i].waiting_time = -1;
    }
    
    shortest_job_first_scheduling (n, process_array);
    return 0;
}

void shortest_job_first_scheduling (int process_count, process process_array[process_count]) {
    int execution_flow[process_count];
    int execution_flow_array_incrementor = 0;
    while (check_process_left(process_count, process_array)) {
        int min_job_first_process_id = fetch_shortest_process(process_count, process_array);
        execution_flow[execution_flow_array_incrementor] = min_job_first_process_id;
        execution_flow_array_incrementor++;
        time_counter += process_array[min_job_first_process_id].burst_time;
        process_array[min_job_first_process_id].completion_time = time_counter;
        process_array[min_job_first_process_id].turn_around_time = process_array[min_job_first_process_id].completion_time - process_array[min_job_first_process_id].arrival_time;
        process_array[min_job_first_process_id].waiting_time = process_array[min_job_first_process_id].turn_around_time - process_array[min_job_first_process_id].burst_time;
    }
    printf("Shortest Job Scheduling Algorithm\n");
    print_statistics(process_count, process_array,execution_flow);
    return;
}

bool check_process_left (int process_count, process process_array[process_count]) {
    for (int i = 0; i<process_count; i++) {
        if (process_array[i].completion_time == -1) {
            return true;
        } else {
            continue;
        }
    }
    return false;
}

int fetch_shortest_process (int process_count, process process_array[process_count]) {
    bool cpu_idle = true;
    int process_id;
    int arrival_time = INT_MAX;
    int burst_time = INT_MAX;
    
    for (int i = 0; i<process_count; i++) {
        if (process_array[i].arrival_time > time_counter) {
            continue;
        } else {
            if (process_array[i].completion_time != -1) {
                continue;
            } else {
                if (burst_time > process_array[i].burst_time) {
                    burst_time = process_array[i].burst_time;
                    process_id = i;
                    cpu_idle = false;
                } else if (burst_time == process_array[i].burst_time) {
                    if (arrival_time > process_array[i].arrival_time) {
                        arrival_time = process_array[i].arrival_time;
                        process_id = i;
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }
        }
    }
    
    if (cpu_idle) {
        for (int i = 0; i<process_count; i++) {
            if (process_array[i].completion_time != -1) {
                continue;
            } else {
                if (arrival_time > process_array[i].arrival_time) {
                    arrival_time = process_array[i].arrival_time;
                    process_id = i;
                } else if (arrival_time == process_array[i].arrival_time) {
                    if (burst_time > process_array[i].burst_time) {
                        burst_time = process_array[i].burst_time;
                        process_id = i;
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }
        }
        arrival_time -= time_counter;
        time_counter += arrival_time;
    }
    return process_id;
}

void print_statistics(int process_count, process process_array[process_count], int execution_flow_array[process_count]) {
    float average_turn_around_time = 0;
    float average_waiting_time = 0;

    printf("+------------+--------------+------------+-----------------+-----------------+---------------+\n");
    printf("| Process ID | Arrival Time | Burst Time | Completion Time | Turn Around Time | Waiting Time |\n");
    printf("+------------+--------------+------------+-----------------+-----------------+---------------+\n");
    
    for (int i = 0; i < process_count; i++) {
        printf("| %*d | %*d | %*d | %*d | %*d | %*d |\n",
               strlen("Process ID"), process_array[i].process_id, 
               strlen("Arrival Time"), process_array[i].arrival_time,
               strlen("Burst Time"), process_array[i].burst_time, 
               strlen("Completion Time"), process_array[i].completion_time,
               strlen("Turn Around Time"), process_array[i].turn_around_time,
               strlen("Waiting Time"), process_array[i].waiting_time);
        
        average_turn_around_time += process_array[i].turn_around_time;
        average_waiting_time += process_array[i].waiting_time;
    }
    average_turn_around_time /= process_count;
    average_waiting_time /= process_count;
    
    printf("+------------+--------------+------------+-----------------+-----------------+---------------+\n");
    printf("Process Execution Order: ");
    for (int i = 0; i<process_count; i++) {
        printf("P%d ",execution_flow_array[i]);
    }
    printf("\nAverage Turn Around Time: %.2f\n", average_turn_around_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
}