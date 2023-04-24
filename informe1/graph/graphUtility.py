import csv
import matplotlib.pyplot as plt

def plot_results(csv_file):
    with open(csv_file) as f:
        reader = csv.DictReader(f)
        data = [(row['Experiment'], row['Dataset'], int(row['Time(us)'])) for row in reader]

    # Sort the data by the numeric part of the filename
    data.sort(key=lambda x: int(x[1].split('_')[1].split('.')[0]))

    # Get a list of unique experiments
    experiments = list(set([d[0] for d in data]))

    fig, ax = plt.subplots()

    # Plot each experiment as a separate line
    for experiment in experiments:
        experiment_data = [(d[1], d[2]) for d in data if d[0] == experiment]
        labels = [d[0] for d in experiment_data]
        values = [d[1] for d in experiment_data]
        ax.plot(labels, values, '-o', linewidth=2, markersize=8, label=experiment)

        for i, v in enumerate(values):
            continue
            #ax.annotate(str(v), xy=(i, v), xytext=(i-0.25, v+5000))

    ax.set_title('Sorting Results')
    ax.set_xlabel('Dataset')
    ax.set_ylabel('Time (us)')
    ax.set_xticklabels(labels, rotation=45, ha='right')
    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.legend()

    plt.show()
plot_results('statistics/results.csv')
