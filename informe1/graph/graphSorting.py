import csv
import matplotlib.pyplot as plt

def plot_results(csv_file):
    with open(csv_file) as f:
        reader = csv.DictReader(f)
        data = [(row['Experiment'], int(row['Entries']), int(row['Time(us)'])) for row in reader]

    # Sort the data by the Entries column
    data.sort(key=lambda x: x[1])

    # Get a list of unique experiments
    experiments = list(set([d[0] for d in data]))

    fig, ax = plt.subplots()

    # Plot each experiment as a separate line
    for experiment in experiments:
        experiment_data = [(d[1], d[2]) for d in data if d[0] == experiment]
        labels = [str(d[0]) for d in experiment_data] # Use Entries as labels
        values = [d[1] for d in experiment_data]
        ax.plot(labels, values, '-o', linewidth=2, markersize=8, label=experiment)

    ax.set_title('Sorting Results')
    ax.set_xlabel('Entries')
    ax.set_ylabel('Time (us)')
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.legend()

    plt.show()

plot_results('statistics/sorting_results.csv')
