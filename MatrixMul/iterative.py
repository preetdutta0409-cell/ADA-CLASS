import pandas as pd
import matplotlib.pyplot as plt
 
df = pd.read_csv("matrixMultIterative.csv")
 
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(11, 4.5))
 
# Linear scale
ax1.plot(df["size"], df["time_seconds"], marker="o", color="tab:blue")
ax1.set_title("Execution time vs matrix size")
ax1.set_xlabel("Matrix size (n x n)")
ax1.set_ylabel("Time (seconds)")
ax1.grid(True, alpha=0.3)
 
# Log-log scale: a straight line with slope ~3 confirms O(n^3)
ax2.loglog(df["size"], df["time_seconds"], marker="o", color="tab:red")
ax2.set_title("Log-log scale (slope ≈ 3 → O(n³))")
ax2.set_xlabel("Matrix size (n)")
ax2.set_ylabel("Time (seconds)")
ax2.grid(True, which="both", alpha=0.3)
 
plt.tight_layout()
plt.savefig("matmul_times.png", dpi=150)
plt.show()