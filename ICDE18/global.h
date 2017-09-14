/**
	1. global
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "input.h"

typedef pair<double,int> pdi;
typedef pair<double,double> pdd;

double calcUtility(const task_t& t, const worker_t& w) {
	return w.arr[t.id];
}


#endif