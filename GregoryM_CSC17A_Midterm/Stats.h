/* 
 * File:   Stats.h
 * Author: Maria Gregory
 *
 * Created on April 19, 2018, 5:48 PM
 */

#ifndef STATS_H
#define STATS_H

struct Stats {
    float avd; // Average value of an integer array
    float median; // Median value of an integer array
    int *mode; // array containing the modes
    int nModes; // number of modes in the array
    int maxFreq; // max frequency of modes
};

#endif /* STATS_H */

