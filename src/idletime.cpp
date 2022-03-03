#include <cstdio>
#include <thread>
#include <time.h>

// setting the idle time
#define IDLETIME 5
extern bool is_idle;
int start;
int idle_time_start;

double getIdleTime()
{
    double idle_time = -1.0;
    while (is_idle)
    {
        idle_time = (double)(clock() - idle_time_start) / CLOCKS_PER_SEC;
    }
    return idle_time;
}
void elapsedTime()
{
    while (1)
    {
        double tmp_time = (double)(clock() - start) / CLOCKS_PER_SEC;

        if (tmp_time > IDLETIME)
        {
            printf("IDLE!!\n");
            idle_time_start = clock();
            is_idle = 1;
            double f = getIdleTime();
            // fflush(stdout);
            if (f >= 0.0)
            {
                printf("idle for -- %lf\n", f);
            }
            start = clock();
        }
    }
}