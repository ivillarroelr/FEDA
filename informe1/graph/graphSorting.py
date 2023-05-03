import csv
import matplotlib.pyplot as plt

# This script plots the results of sorting experiments
# for different dataset types as a function of the number
# of entries in each experiment.

def plot_results(csv_file):
    with open(csv_file) as f:
        reader = csv.DictReader(f)
        data = [(row['Experiment'], row['Dataset'], int(row['Entries']), int(row['Time(us)'])) for row in reader]

    # Sort the data by the Entries column
    data.sort(key=lambda x: x[2])

    # Get a list of unique dataset types
    dataset_types = list(set([d[1].split('_')[1] for d in data]))

    fig, axs = plt.subplots(nrows=2, ncols=2, figsize=(12, 8))

    for i, dataset_type in enumerate(dataset_types):
        ax = axs[i // 2, i % 2]

        dataset_data = [(d[0], d[2], d[3]) for d in data if d[1].split('_')[1] == dataset_type]

        # Sort the data by the Entries column
        dataset_data.sort(key=lambda x: x[1])

        # Get a list of unique experiments
        experiments = list(set([d[0] for d in dataset_data]))

        # Plot each experiment as a separate line
        for experiment in experiments:
            experiment_data = [(d[1] / 1000, d[2]) for d in dataset_data if d[0] == experiment]
            labels = [str(d[0]) for d in experiment_data] # Use Entries as labels (in thousands)
            values = [d[1] for d in experiment_data]
            ax.plot(labels, values, '-', linewidth=2, markersize=8, label=experiment)

        ax.set_title(f'{dataset_type.capitalize()} Dataset', fontsize=16)
        ax.set_xlabel('Entries (thousands)', fontsize=12)
        ax.set_ylabel('Time (microseconds)', fontsize=12)
        ax.grid(True)
        ax.spines['right'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.legend(fontsize=10)

    plt.suptitle('Sorting Results for Different Dataset Types', fontsize=20)
    plt.tight_layout()
    plt.show()

plot_results('../statistics/sorting_results.csv')

