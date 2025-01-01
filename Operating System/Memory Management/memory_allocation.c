#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

struct MemoryBlock {
    int totalSpace;
    bool allocated;
    int remainingSpace;
};

struct ProcessBlock {
    int size;
    bool allocated;
    int memoryAddress;
};

void printTable(struct MemoryBlock MB[], int memoryBlockCount, struct ProcessBlock PB[], int processBlockCount) {
    printf("+-------------+--------------+--------------+-------------+-----------------+\n");
    printf("| Process No. | Process Size | Memory Block | Total Space | Remaining Space |\n");
    printf("+-------------+--------------+--------------+-------------+-----------------+\n");
    
    for (int i = 0; i < processBlockCount; i++) {
        printf("| %*d | %*d |",strlen("Process No."),i,strlen("Process Size"),PB[i].size);
        if (PB[i].memoryAddress != -1) {
            printf(" %*d | %*d | %*d |\n",strlen("Memory Block"),PB[i].memoryAddress,strlen("Total Space"),MB[PB[i].memoryAddress].totalSpace,strlen("Remaining Space"),MB[PB[i].memoryAddress].remainingSpace);
        } else {
            printf(" %12s | %11s | %15s |\n","-","-","-");
        }
        printf("+-------------+--------------+--------------+-------------+-----------------+\n");
    }
    
    int memoryWastage = 0;
    printf("Total Memory Wastage :");
    for (int j = 0; j < memoryBlockCount; j++) {
        memoryWastage += MB[j].remainingSpace;
    }
    printf("%d\n",memoryWastage);
}

void firstFit(struct MemoryBlock MB[], int memoryBlockCount, struct ProcessBlock PB[], int processBlockCount) {
    for(int i = 0; i < processBlockCount; i++) {
        for (int j = 0; j < memoryBlockCount; j++) {
            if (!MB[j].allocated && MB[j].totalSpace >= PB[i].size) {
                PB[i].allocated = true;
                PB[i].memoryAddress = j;
                    
                MB[j].allocated = true;
                MB[j].remainingSpace = MB[j].totalSpace - PB[i].size;
                break;
            }
        }
    }
    printTable(MB, memoryBlockCount ,PB, processBlockCount);
}

void bestFit(struct MemoryBlock MB[], int memoryBlockCount, struct ProcessBlock PB[], int processBlockCount) {
    
    int minProcessMemoryDifference;
    int MemoryBlockID;
    int tempDifference;
    
    for(int i = 0; i < processBlockCount; i++) {
        minProcessMemoryDifference = INT_MAX;
        MemoryBlockID = -1;
        for (int j = 0; j < memoryBlockCount; j++) {
            if (!MB[j].allocated && MB[j].totalSpace >= PB[i].size) {
                tempDifference = MB[j].totalSpace - PB[i].size;
                if(tempDifference < minProcessMemoryDifference) {
                    MemoryBlockID = j;
                    minProcessMemoryDifference = tempDifference;
                }
            }
        }
        if (MemoryBlockID != -1) {
            MB[MemoryBlockID].allocated = true;
            MB[MemoryBlockID].remainingSpace = MB[MemoryBlockID].totalSpace - PB[i].size;
            
            PB[i].allocated = true;
            PB[i].memoryAddress = MemoryBlockID;
        }
    }
    printTable(MB, memoryBlockCount ,PB, processBlockCount);
}

void worstFit(struct MemoryBlock MB[], int memoryBlockCount, struct ProcessBlock PB[], int processBlockCount) {
    int maxProcessMemoryDifference = INT_MIN;
    int MemoryBlockID;
    int tempDifference;
    
    for(int i = 0; i < processBlockCount; i++) {
        maxProcessMemoryDifference = INT_MIN;
        MemoryBlockID = -1;
        for (int j = 0; j < memoryBlockCount; j++) {
            if (!MB[j].allocated && MB[j].totalSpace >= PB[i].size) {
                tempDifference = MB[j].totalSpace - PB[i].size;
                if(tempDifference > maxProcessMemoryDifference) {
                    MemoryBlockID = j;
                    maxProcessMemoryDifference = tempDifference;
                    
                }
            }        
        }
        if (MemoryBlockID != -1) {
            MB[MemoryBlockID].allocated = true;
            MB[MemoryBlockID].remainingSpace = MB[MemoryBlockID].totalSpace - PB[i].size;
            
            PB[i].allocated = true;
            PB[i].memoryAddress = MemoryBlockID;
        }
    }
    printTable(MB, memoryBlockCount ,PB, processBlockCount);
}

int main () {
    printf("Input no of Processes :");
    int n;
    scanf("%d",&n);
    
    printf("Input Process Sizes :");
    struct ProcessBlock PB[n];
    for (int i = 0 ; i<n ; i++) {
        scanf("%d",&PB[i].size);
        PB[i].allocated = false;
        PB[i].memoryAddress = -1;
    }
    
    printf("Input no of Memory Blocks :");
    int m;
    scanf("%d",&m);
    
    printf("Input Memory Block Sizes :");
    struct MemoryBlock MB[m];
    for (int i = 0 ; i<m ; i++) {
        scanf("%d",&MB[i].totalSpace);
        MB[i].allocated = false;
        MB[i].remainingSpace = 0;
    }
    
    printf("\nFirst Fit Allocation\n");
    firstFit(MB,m,PB,n);
    
    // Reset the memory blocks and processes for the next allocation strategies
    for (int i = 0; i < m; i++) {
        MB[i].allocated = false;
    }
    for (int i = 0; i < n; i++) {
        PB[i].allocated = false;
        PB[i].memoryAddress = -1;
    }
    
    printf("\nBest Fit Allocation\n");
    bestFit(MB,m,PB,n);
    
    // Reset the memory blocks and processes for the next allocation strategies
    for (int i = 0; i < m; i++) {
        MB[i].allocated = false;
        MB[i].remainingSpace = 0;
    }
    for (int i = 0; i < n; i++) {
        PB[i].allocated = false;
        PB[i].memoryAddress = -1;
    }
    
    printf("\nWorst Fit Allocation\n");
    worstFit(MB,m,PB,n);
    
    return 0;
}