#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include "log.h"

#define USING_MS

void program_start(program_t *prog) {
	clock_gettime(CLOCK_REALTIME, &prog->real_start);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &prog->proc_start);
}

void program_end(FILE *fout, program_t *prog, char *msg) {
	struct timespec real_end;
	struct timespec proc_end;

	clock_gettime(CLOCK_REALTIME, &real_end);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc_end);

	#ifdef USING_MS
	double real_btime = prog->real_start.tv_sec*1000. + (double)prog->real_start.tv_nsec / 1e6;
	double real_etime = real_end.tv_sec*1000. + (double)real_end.tv_nsec / 1e6;
	#else  /* USING_MS */
	double real_btime = (double)prog->real_start.tv_sec + (double)prog->real_start.tv_nsec / 1e9;
	double real_etime = (double)real_end.tv_sec + (double)real_end.tv_nsec / 1e9;
	#endif /* USING_MS */
	double real_time = real_etime - real_btime;

	#ifdef USING_MS
	double proc_btime = prog->proc_start.tv_sec*1000. + (double)prog->proc_start.tv_nsec / 1e6;
	double proc_etime = proc_end.tv_sec*1000. + (double)proc_end.tv_nsec / 1e6;
	#else  /* USING_MS */
	double proc_btime = (double)prog->proc_start.tv_sec + (double)prog->proc_start.tv_nsec / 1e9;
	double proc_etime = (double)proc_end.tv_sec + (double)proc_end.tv_nsec / 1e9;
	#endif /* USING_MS */
	double proc_time = proc_etime - proc_btime;

	char start_time[64], end_time[64];
	char *format = "%Y-%m-%d %H:%M:%S";

	strftime(start_time, (size_t)64, format, localtime(&prog->real_start.tv_sec));
	strftime(end_time, (size_t)64, format, localtime(&real_end.tv_sec));

	fprintf(fout, "\n%s\n", msg);
	fprintf(fout, "    Start: %s, End: %s.\n", start_time, end_time);
	#ifdef USING_MS
	fprintf(fout, "    CPU: %.3lfms, Real: %.3lfms.\n\n", proc_time, real_time);
	#else  /* USING_MS */
	fprintf(fout, "    CPU: %.3lfms, Real: %.3lfms.\n\n", proc_time, real_time);
	#endif /* USING_MS */
}
