import csv
import matplotlib.pyplot as plt
import locale

# This script plots the results of matrix product experiments
# as a function of the size of the matrices being multiplied.

def plot_results(csv_file, title, ax):
    with open(csv_file) as f:
        reader = csv.DictReader(f)
        data = [(row['Experiment'], int(row['Dataset']), int(row['m']), int(row['Time(us)'])) for row in reader]

    # Sort the data by the m column
    data.sort(key=lambda x: x[2])

    # Get a list of unique experiments
    experiments = list(set([d[0] for d in data]))

    # Plot each experiment as a separate line
    for experiment in experiments:
        experiment_data = [(d[2], d[3]) for d in data if d[0] == experiment]
        labels = [locale.format_string("%d", d[0], grouping=True) for d in experiment_data] # Use m as labels with thousands separator
        values = [d[1] for d in experiment_data]
        ax.plot(labels, values, '-', linewidth=2, markersize=8, label=experiment)

    ax.set_title(title, fontsize=20)
    ax.set_xlabel('m (thousands)', fontsize=16)
    ax.set_ylabel('Time (microseconds)', fontsize=16)
    ax.grid(True)
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.legend(fontsize=14)

    return ax

# Create a figure with 2 subplots side by side
fig, (ax1, ax2) = plt.subplots(ncols=2, figsize=(16, 6))

# Plot the square graph
plot_results('statistics/matrix_square_results.csv', 'Matrix Square Results', ax1)

# Plot the rectangle graph
plot_results('statistics/matrix_rectangle_results.csv', 'Matrix Rectangle Results', ax2)

plt.show()
