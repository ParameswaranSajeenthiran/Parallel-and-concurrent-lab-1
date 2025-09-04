#include <stdio.h>
#include <sys/stat.h>
#include "tests/Config.h"
#include "tests/Mutex.h"
#include "tests/ReadWriteLock.h"
#include "tests/Serial.h"
#include <math.h>

/**
 * Calculate required sample size for ±5% accuracy and 95% confidence level
 *
 * @param mean  - average runtime from pilot runs
 * @param std   - standard deviation from pilot runs
 * @param conf  - confidence level (default 0.95)
 * @param rel_err - relative error (default 0.05 for ±5%)
 * @return required sample size (rounded up)
 */
int required_sample_size(double mean, double std, double conf, double rel_err) {
    double z;
    // z-values: 90% → 1.645, 95% → 1.96, 99% → 2.576
    if (fabs(conf - 0.90) < 1e-6) z = 1.645;
    else if (fabs(conf - 0.95) < 1e-6) z = 1.96;
    else if (fabs(conf - 0.99) < 1e-6) z = 2.576;
    else z = 1.96;  // default to 95%

    double numerator = z * std;
    double denominator = rel_err * mean;
    double n = (numerator / denominator) * (numerator / denominator);

    return (int)ceil(n);
}

int main() {
    int min_required = 0;  // will store the minimmium required N across configs

    mkdir("output", 0777);
    double serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime;
    double rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime;
    const int N = 114;   // number of iterations per case

    FILE *fp;
    int case_num;
    struct Config config;

    /*===================
    |       case 1      |
    ====================*/
    case_num = 1;
    config = (struct Config){1000, 10000, 0.99, 0.005, 0.005};
    fp = fopen("output/Case_1.csv", "w+");
    if (!fp) {
        perror("Error opening Case_1.csv");
        return 1;
    }
    fprintf(fp, "Serial, mut_t1, mut_t2, mut_t4, mut_t8, rw_t1, rw_t2, rw_t4, rw_t8\n");

    for (size_t i = 0; i < N; i++) {
        serial_runtime = run_serial(config);
        mut_t1_runtime = runMutex(1, config);
        mut_t2_runtime = runMutex(2, config);
        mut_t4_runtime = runMutex(4, config);
        mut_t8_runtime = runMutex(8, config);
        rw_t1_runtime  = runReadWriteLock(1, config);
        rw_t2_runtime  = runReadWriteLock(2, config);
        rw_t4_runtime  = runReadWriteLock(4, config);
        rw_t8_runtime  = runReadWriteLock(8, config);
        printf("Case 1, Iteration %zu: Serial: %f, Mutex 1: %f, Mutex 2: %f, Mutex 4: %f, Mutex 8: %f, RWLock 1: %f, RWLock 2: %f, RWLock 4: %f, RWLock 8: %f\n",
               i + 1, serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime,
               rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);

        fprintf(fp, "%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime,
                rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
    }
    fclose(fp);

    /*===================
    |       case 2      |
    ====================*/
    case_num = 2;
    config = (struct Config){1000, 10000, 0.9, 0.05, 0.05};   // adjust as per your case 2 config
    fp = fopen("output/Case_2.csv", "w+");
    if (!fp) {
        perror("Error opening Case_2.csv");
        return 1;
    }
    fprintf(fp, "Serial, mut_t1, mut_t2, mut_t4, mut_t8, rw_t1, rw_t2, rw_t4, rw_t8\n");

    for (size_t i = 0; i < N; i++) {
        serial_runtime = run_serial(config);
        mut_t1_runtime = runMutex(1, config);
        mut_t2_runtime = runMutex(2, config);
        mut_t4_runtime = runMutex(4, config);
        mut_t8_runtime = runMutex(8, config);
        rw_t1_runtime  = runReadWriteLock(1, config);
        rw_t2_runtime  = runReadWriteLock(2, config);
        rw_t4_runtime  = runReadWriteLock(4, config);
        rw_t8_runtime  = runReadWriteLock(8, config);
        printf("Case 2, Iteration %zu: Serial: %f, Mutex 1: %f, Mutex 2: %f, Mutex 4: %f, Mutex 8: %f, RWLock 1: %f, RWLock 2: %f, RWLock 4: %f, RWLock 8: %f\n",
                      i + 1, serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime,
                      rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
        fprintf(fp, "%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime,
                rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
    }
    fclose(fp);

    /*===================
    |       case 3      |
    ====================*/
    case_num = 3;
    config = (struct Config){1000, 10000, 0.5, 0.25, 0.25};   // adjust as per your case 3 config
    fp = fopen("output/Case_3.csv", "w+");
    if (!fp) {
        perror("Error opening Case_3.csv");
        return 1;
    }
    fprintf(fp, "Serial, mut_t1, mut_t2, mut_t4, mut_t8, rw_t1, rw_t2, rw_t4, rw_t8\n");

    for (size_t i = 0; i < N; i++) {
        serial_runtime = run_serial(config);
        mut_t1_runtime = runMutex(1, config);
        mut_t2_runtime = runMutex(2, config);
        mut_t4_runtime = runMutex(4, config);
        mut_t8_runtime = runMutex(8, config);
        rw_t1_runtime  = runReadWriteLock(1, config);
        rw_t2_runtime  = runReadWriteLock(2, config);
        rw_t4_runtime  = runReadWriteLock(4, config);
        rw_t8_runtime  = runReadWriteLock(8, config);
        printf("Case 3, Iteration %zu: Serial: %f, Mutex 1: %f, Mutex 2: %f, Mutex 4: %f, Mutex 8: %f, RWLock 1: %f, RWLock 2: %f, RWLock 4: %f, RWLock 8: %f\n",
                      i + 1, serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime,
                      rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
        fprintf(fp, "%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime,
                rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
    }
    fclose(fp);

    printf("Experiment completed successfully!\n");


const char *cases[] = {"output/Case_1.csv", "output/Case_2.csv", "output/Case_3.csv"};
    const char *avg_filename = "output/Averages.csv";
    char line[1024];

    for (int c = 0; c < 3; c++) {
        double sum[9] = {0};
        double sq_sum[9] = {0};
        double avg[9], std[9];

        fp = fopen(cases[c], "r");
        if (!fp) {
            perror(cases[c]);
            continue;
        }

        // Skip header
        if (!fgets(line, sizeof(line), fp)) {
            fclose(fp);
            continue;
        }

        int count = 0;
        // Read all rows
        while (fgets(line, sizeof(line), fp)) {
            double values[9];
            if (sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                       &values[0], &values[1], &values[2], &values[3],
                       &values[4], &values[5], &values[6], &values[7], &values[8]) != 9) {
                fprintf(stderr, "Invalid line in %s: %s", cases[c], line);
                continue;
            }
            for (int j = 0; j < 9; j++) {
                sum[j] += values[j];
                sq_sum[j] += values[j] * values[j];
            }
            count++;
        }
        fclose(fp);

        if (count == 0) continue;

        // compute averages and std dev
        for (int j = 0; j < 9; j++) {
            avg[j] = sum[j] / count;
            std[j] = sqrt((sq_sum[j] / count) - (avg[j] * avg[j]));
            int req_n = required_sample_size(avg[j], std[j], 0.95, 0.05);
            if (req_n > min_required) min_required = req_n;

            // printf("Implementation %d -> Mean=%.2f Std=%.2f Required N=%d\n",
            //        j, avg[j], std[j], req_n);
        }


        // prepare output filename
        char out_filename[256];
        snprintf(out_filename, sizeof(out_filename), "output/Case_%d_Result.csv", c+1);

        FILE *fp_out = fopen(out_filename, "w+");
        if (!fp_out) {
            perror(out_filename);
            continue;
        }

        // write header
        fprintf(fp_out, "Implementation,"
                        "1 Average,1 Std,"
                        "2 Average,2 Std,"
                        "4 Average,4 Std,"
                        "8 Average,8 Std\n");

        // write Serial row
        fprintf(fp_out, "Serial,%.2f,%.2f,,,,,,,\n", avg[0], std[0]);

        // write One mutex for entire list row
        fprintf(fp_out, "One mutex for entire list,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                avg[1], std[1], avg[2], std[2], avg[3], std[3], avg[4], std[4]);

        // write Read-Write lock row
        fprintf(fp_out, "Read-Write lock,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                avg[5], std[5], avg[6], std[6], avg[7], std[7], avg[8], std[8]);

        fclose(fp_out);

        printf("Case_%d results written to %s\n", c+1, out_filename);
    }
}

