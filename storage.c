#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/statvfs.h>

#define BLOCK_SIZE 1024

void printProgressBar(float percentage) {
    int totalBars = 30;
    int currentBars = (int)(percentage * totalBars);
    int remainingBars = totalBars - currentBars;
    
    printf("[");
    for (int i = 0; i < currentBars; i++) {
        printf("=");
    }
    for (int i = 0; i < remainingBars; i++) {
        printf(" ");
    }
    printf("] %.2f%%\n", percentage * 100);
}

void printStorageUsage(const char* path) {
    struct statvfs stat;
    
    if (statvfs(path, &stat) != 0) {
        printf("Failed to get storage information!\n");
        return;
    }
    
    uint64_t totalSpace = stat.f_blocks * stat.f_frsize;
    uint64_t freeSpace = stat.f_bfree * stat.f_frsize;
    float usagePercentage = 1.0 - ((float)freeSpace / (float)totalSpace);
    
    printf("Total Space: %.2f GB\n", (double)totalSpace / (1024 * 1024 * 1024));
    printf("Free Space: %.2f GB\n", (double)freeSpace / (1024 * 1024 * 1024));
    
    printProgressBar(usagePercentage);
}

int main() {
    const char* storagePath = "/"; // Change this to the desired storage path
    
    printStorageUsage(storagePath);
    
    return 0;
}
