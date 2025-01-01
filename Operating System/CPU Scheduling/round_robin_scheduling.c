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

struct process_execution_time_block {
    int process_id;
    int arrival_time;
    int execution_time_left;
} typedef process_execution_queue;

void round_robin_scheduling (int, process [], int);
bool check_process_left (int, process_execution_queue []);
int fetch_queue_process (int, process_execution_queue [], int);
int fetch_process_id (int, int, process []);
void print_statistics (int, process []);
int compare_by_arrival_time (const void *a, const void *b);

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
    int time_quantum;
    printf("Type Time Quantum: ");
    scanf("%d",&time_quantum);
    round_robin_scheduling (n, process_array, time_quantum);
    return 0;
}

void round_robin_scheduling (int process_count, process process_array[process_count], int time_quantum) {
    process_execution_queue ready_queue[process_count];
    
    for(int i = 0; i<process_count; i++) {
        ready_queue[i].process_id = process_array[i].process_id;
        ready_queue[i].arrival_time = process_array[i].arrival_time;
        ready_queue[i].execution_time_left = process_array[i].burst_time;
    }

    qsort(ready_queue, process_count, sizeof(process_execution_queue), compare_by_arrival_time);

    int ready_queue_pointer = 0;
    int process_array_pointer;
    
    printf("Execution Flow Order: ");
    while (check_process_left(process_count, ready_queue)) {
        ready_queue_pointer = fetch_queue_process(process_count, ready_queue, ready_queue_pointer);
        
        process_array_pointer = fetch_process_id (ready_queue[ready_queue_pointer].process_id, process_count, process_array);
     
        if (ready_queue[ready_queue_pointer].execution_time_left > time_quantum) {
            time_counter += time_quantum;
            ready_queue[ready_queue_pointer].execution_time_left -= time_quantum;
        } else if (ready_queue[ready_queue_pointer].execution_time_left == 0){
            continue;
        } else {
            time_counter += ready_queue[ready_queue_pointer].execution_time_left;
            ready_queue[ready_queue_pointer].execution_time_left = 0;
            process_array[process_array_pointer].completion_time = time_counter;
            process_array[process_array_pointer].turn_around_time = process_array[process_array_pointer].completion_time - process_array[process_array_pointer].arrival_time;
            process_array[process_array_pointer].waiting_time = process_array[process_array_pointer].turn_around_time - process_array[process_array_pointer].burst_time;
            
        }
        printf("P%d ",ready_queue[ready_queue_pointer].process_id);
        ready_queue_pointer = (ready_queue_pointer+1)%process_count;
    }
    printf("\nRound Robin Scheduling Algorithm\n");
    print_statistics(process_count, process_array);
    return;
}

bool check_process_left (int process_count, process_execution_queue ready_queue[process_count]) {
    for (int i = 0; i<process_count; i++) {
        if (ready_queue[i].execution_time_left != 0) {
            return true;
        } else {
            continue;
        }
    }
    return false;
}

int fetch_queue_process(int process_count, process_execution_queue ready_queue[process_count], int ready_queue_pointer) {
    int time_difference;

    while (true) {
        if (ready_queue[ready_queue_pointer].execution_time_left == 0) {
            ready_queue_pointer = (ready_queue_pointer + 1) % process_count;
            continue;
        }

        if (ready_queue[ready_queue_pointer].arrival_time > time_counter) {
            time_difference = ready_queue[ready_queue_pointer].arrival_time - time_counter;
            time_counter += time_difference;
        } else {
            break; 
        }
        ready_queue_pointer = (ready_queue_pointer + 1) % process_count;
    }
    return ready_queue_pointer;
}


int fetch_process_id (int process_id, int process_count, process process_array[process_count]) {
    int process_id_index;

    for (int i = 0; i<process_count; i++) {
        if (process_id == process_array[i].process_id) {
            process_id_index = i;
            break;
        }
    }
    return process_id_index;
}

int compare_by_arrival_time(const void *a, const void *b) {
    process_execution_queue *p1 = (process_execution_queue *)a;
    process_execution_queue *p2 = (process_execution_queue *)b;
    return p1->arrival_time - p2->arrival_time;
}


void print_statistics(int process_count, process process_array[process_count]) {
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
    printf("Average Turn Around Time: %.2f\n", average_turn_around_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
}