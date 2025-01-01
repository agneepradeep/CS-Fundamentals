#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void input_matrix(int rows, int columns, int matrix[rows][columns]) {
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<columns; j++) {
            scanf("%d",&matrix[i][j]);
        }
    }
    return;
}

bool check_process_status(int rows, bool process_status[rows]) {
    for (int i = 0; i<rows; i++) {
        if (process_status[i] == false) {
            return false;
        } else {
            continue;
        }
    }
    return true;
}

int main() {
    printf("Type no. of process: ");
    int p;
    scanf("%d",&p);
    bool process_status[p];
    for (int i = 0; i<p; i++) {
        process_status[i] = false;
    }

    printf("Type no. of resources: ");
    int r;
    scanf("%d",&r);

    int available_resources[r];
    printf("Type Available Resources: ");
    for (int i = 0; i<r; i++) {
        scanf("%d",&available_resources[i]);
    }

    int allocation_matrix[p][r];
    int max_matrix[p][r];
    int need_matrix[p][r];

    printf("Type Allocation Matrix:\n");
    input_matrix(p,r,allocation_matrix);

    printf("Type Max Matrix:\n");
    input_matrix(p,r,max_matrix);

    /**Compute Needed Resources */
    for (int i = 0; i<p; i++) {
        for (int j = 0; j<r; j++) {
            need_matrix[i][j] = max_matrix[i][j] - allocation_matrix[i][j];
        }
    }

    /**Check Process State */
    int order_matrix[p];
    int arr_pointer = 0;
    int checkCount = 0;
    int compareCount = 0;
    do {
        if (check_process_status(p, process_status)) {
            printf("Process are in safe State\n");
            printf("Order of Execution :");
            for (int i = 0; i<p; i++) {
                printf("P%d ",order_matrix[i]);
            }
            return 0;
        }
        checkCount = 0;
        compareCount = 0;
        for (int i = 0; i<p; i++) {
            if (process_status[i] == true) {
                continue;
            }
            for(int j = 0; j<r; j++) {
                if (need_matrix[i][j] <= available_resources[j]) {
                    compareCount++;
                }
            }
        
            if(compareCount == r) {
                for (int j = 0; j<r; j++) {
                    available_resources[j] += need_matrix[i][j];
                    need_matrix[i][j] = 0;
                }
                process_status[i] = true;
                order_matrix[arr_pointer] = i;
                arr_pointer++;
                checkCount++;
            } else {
                continue;
            }
        }
    } while (checkCount != 0);
    printf("Process are not in safe state. Deadlock can occur\n");
    return 0;
}