#include <stdio.h>
#include <stdbool.h>

bool checkPageReference(int f[], int p,int l) {
    for (int i = 0; i< l; i++) {
        if (f[i] == p) {
            return true;
        }
    }
    return false;
}

int main () {
    printf("Enter number of page references: ");
    int n;
    scanf("%d",&n);

    int pages[n];
    printf("Enter the page references: ");
    for (int i = 0; i< n; i++) {
        scanf("%d",&pages[i]);
    }

    int frameSize;
    printf("Enter the frame size: ");
    scanf("%d",&frameSize);

    int frame[frameSize];
    int framePointer = 0;
    int pageFault = 0;

    for (int i = 0; i< frameSize ; i++) {
        frame[i] = -1;
    }
    
    int hit = 0;
    printf("Page Reference\tPage Fault\tFrame\n");
    for (int i = 0; i < n; i++) {
        if (i < frameSize) {
            if (checkPageReference(frame,pages[i],frameSize)) {
                printf("[%d]\t\thit\t\t[",pages[i]);
                hit++;
            } else {
                framePointer = framePointer%frameSize;
                frame[framePointer] = pages[i];
                printf("[%d]\t\tMiss\t\t[",pages[i]);
                pageFault++;   
                framePointer++;
            }
            
            for(int j = 0 ; j < framePointer-1; j++) {
                printf("%d ",frame[j]);
            }
            printf("%d]\n",frame[framePointer-1]);
        } else {
            if (checkPageReference(frame,pages[i],frameSize)) {
                printf("[%d]\t\tHit\t\t\t[",pages[i]);
                hit ++;
            } else {
                printf("[%d]\t\tMiss\t\t[",pages[i]);
                framePointer = (framePointer)%frameSize;
                frame[framePointer] = pages[i];
                framePointer ++;
                pageFault ++;
            }
            for(int j = 0 ; j < frameSize-1; j++) {
                printf("%d ",frame[j]);
            }
            printf("%d]\n",frame[frameSize-1]);
        }
    }
    float hitRatio = ((hit)/(float)n)*100;
    printf("Page Fault :%d\n",pageFault);
    printf("Hit Rate :%.2f%\n",hitRatio);
}