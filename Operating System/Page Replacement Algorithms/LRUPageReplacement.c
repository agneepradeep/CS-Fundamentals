#include <stdio.h>
#include <stdbool.h>

struct Frame {
    int Rank;
    int Page;
};

bool checkPageReference(struct Frame f[], int frameSize, int P) {
    for (int i = 0; i < frameSize; i++) {
        if (f[i].Page == P) {
            return true;
        }
    }
    return false;
}

int pickLastRankIndex(struct Frame f[], int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (f[i].Rank == frameSize) {
            return i;
        } else if (f[i].Page == -1) {  // If a frame is empty, choose it immediately
            return i;
        }
    }
    return 0;  // Fallback to first frame if no valid one is found
}

void rankUpdate(struct Frame f[], int frameSize, int P, int leastRecentlyUsedIndex) {
    int currentRank = f[leastRecentlyUsedIndex].Rank;
    f[leastRecentlyUsedIndex].Rank = 1;  // Reset the rank of the recently used page
    
    for (int i = 0; i < frameSize; i++) {
        if (i != leastRecentlyUsedIndex && f[i].Rank != -1 && f[i].Rank < currentRank) {
            f[i].Rank++;  // Increment the rank of other pages
        }
    }
}

void printFrame(struct Frame f[], int frameSize) {
    printf("[");
    for (int i = 0; i < frameSize; i++) {
        if (f[i].Page != -1) {
            printf("%d", f[i].Page);
            if (i != frameSize - 1) {
                printf(" ");
            }
        }
    }
    printf("]\n");
}

void LRUPageReplacement(int pages[], int n, struct Frame f[], int frameSize) {
    printf("Page Reference\tPage Fault\tFrame\n");
    
    for (int i = 0; i < n; i++) {
        if (checkPageReference(f, frameSize, pages[i])) {  // Page hit
            int pageIndex;
            for (int j = 0; j < frameSize; j++) {
                if (f[j].Page == pages[i]) {
                    pageIndex = j;
                    break;
                }
            }
            rankUpdate(f, frameSize, pages[i], pageIndex);
            
            printf("[%d]\t\tHit\t\t", pages[i]);
            printFrame(f, frameSize);
        } else {  // Page miss
            int lastRankIndex = pickLastRankIndex(f, frameSize);
            f[lastRankIndex].Page = pages[i];  // Replace the least recently used page
            rankUpdate(f, frameSize, pages[i], lastRankIndex);
            
            printf("[%d]\t\tMiss\t\t", pages[i]);
            printFrame(f, frameSize);
        }
    }
}

int main() {
    printf("Input no. of Page References: ");
    int n;
    scanf("%d", &n);
    
    printf("Input Page References: ");
    int pages[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Input Frame Size: ");
    int frameSize;
    scanf("%d", &frameSize);
    
    struct Frame f[frameSize];
    for (int i = 0; i < frameSize; i++) {
        f[i].Page = -1;  // Initialize pages to -1 (empty)
        f[i].Rank = frameSize;  // Initialize all ranks as the maximum possible value (LRU state)
    }
    
    LRUPageReplacement(pages, n, f, frameSize);
    return 0;
}