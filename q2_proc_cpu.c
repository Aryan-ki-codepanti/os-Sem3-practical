#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("\nKernel version\n");
    system("cat /proc/version|awk '{print $1,$2, $3}'");

    printf("\nCPU Type:\n");
    system("cat /proc/cpuinfo|awk 'NR==3'");  // CPU family
    system("cat /proc/cpuinfo|awk 'NR==8'");  // CPU MHz
    system("cat /proc/cpuinfo|awk 'NR==13'"); // number of cores

    printf("\nCPU Model:\n");
    system("cat /proc/cpuinfo|awk 'NR==5'|awk ' {print $4,$5,$6,$8,$9}'");
    return 0;
}