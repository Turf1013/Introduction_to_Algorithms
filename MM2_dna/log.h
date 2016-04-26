#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

typedef struct {
	struct timespec real_start;
	struct timespec proc_start;
} program_t;

void program_start(program_t *prog);
void program_end(FILE *fout, program_t *prog, char *msg);

#endif /* LOG_H */