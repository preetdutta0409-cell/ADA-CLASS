import pandas as pd
import matplotlib.pyplot as plt
 
df = pd.read_csv("times_strassen.csv")
 
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(11, 4.5))
 
for ax in (ax1, ax2):
    ax.plot(df["size"], df["iterative"], marker="o", label="Iterative")
    ax.plot(df["size"], df["recursive"], marker="s", label="Recursive (8 mults)")
    ax.plot(df["size"], df["strassen"], marker="^", label="Strassen (7 mults)")
    ax.set_xlabel("Matrix size (n x n)")
    ax.set_ylabel("Time (seconds)")
    ax.legend()
 
# Linear scale
ax1.set_title("Execution time vs matrix size")
ax1.grid(True, alpha=0.3)
 
# Log-log scale
ax2.set_xscale("log", base=2)
ax2.set_yscale("log")
ax2.set_title("Log-log scale")
ax2.grid(True, which="both", alpha=0.3)
 
plt.tight_layout()
plt.savefig("matmul_strassen_times.png", dpi=150)
plt.show()