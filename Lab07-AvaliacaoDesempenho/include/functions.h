#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double sum_vector_critical(double *vector, unsigned long length, int num_threads);

double sum_vector_reduction(double *vector, unsigned long length, int num_threads);

double measure_time(double (*func)(double*, unsigned long, int), 
                 double *vector, unsigned long length, int num_threads);

#endif // FUNCTIONS_H