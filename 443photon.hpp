#ifndef _INC_443PHOTON
#define _INC_443PHOTON
#include<sys/time.h>

/** @file */

double get_dtime(void){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((double)(tv.tv_sec)
            + (double)(tv.tv_usec) * 0.001 * 0.001);
}

#endif
