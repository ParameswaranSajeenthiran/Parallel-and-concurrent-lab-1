import pandas as pd
import matplotlib.pyplot as plt

cases = [
    ("Case 1", "output/Case_1_Result.csv"),
    ("Case 2", "output/Case_2_Result.csv"),
    ("Case 3", "output/Case_3_Result.csv"),
]

# threads considered (Serial = 0 threads, then 1,2,4,8)
thread_counts = [0, 1, 2, 4, 8]

for case_name, filename in cases:
    df = pd.read_csv(filename, index_col=False)

    print(df)  # debug
    print(df.columns)
    print(df["Implementation"])

    # Extract serial average as float
    serial_avg = float(df.loc[df["Implementation"] == "Serial"]["1 Average"].values[0])
    print(serial_avg)

    # Extract mutex and rw averages
    mutex_avg_row = df.loc[df["Implementation"] == "One mutex for entire list"]
    rw_avg_row = df.loc[df["Implementation"] == "Read-Write lock"]

    mutex_avgs = [
        serial_avg,
        float(mutex_avg_row["1 Average"].values[0]),
        float(mutex_avg_row["2 Average"].values[0]),
        float(mutex_avg_row["4 Average"].values[0]),
        float(mutex_avg_row["8 Average"].values[0])
    ]

    rw_avgs = [
        serial_avg,
        float(rw_avg_row["1 Average"].values[0]),
        float(rw_avg_row["2 Average"].values[0]),
        float(rw_avg_row["4 Average"].values[0]),
        float(rw_avg_row["8 Average"].values[0])
    ]

    plt.figure(figsize=(8,6))
    plt.plot(thread_counts, mutex_avgs, marker="o", label="Mutex")
    plt.plot(thread_counts, rw_avgs, marker="s", label="RW Lock")
    plt.axhline(y=serial_avg, color="gray", linestyle="--", label="Serial baseline")

    plt.title(f"Average Execution Time vs Threads ({case_name})")
    plt.xlabel("Number of Threads")
    plt.ylabel("Execution Time (Average) (micro-seconds)")
    plt.xticks(thread_counts)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"output/{case_name.replace(' ', '_')}_plot.png")
    plt.close()

print("Plots saved in output/ as Case_1_plot.png, Case_2_plot.png, Case_3_plot.png")
