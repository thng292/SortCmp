import matplotlib.pyplot as plt

def graph_plot():
    file = open("output.csv", "r")
    lines = file.readlines()
    file.close()
    times = list(map(int, lines[0].split(",")[1:]))
    for line in lines[1:]:
        line = line.strip().split(",")
        i = 1
        while i < len(line):
            try:
                line[i] = float(line[i])
            except:
                break
            i += 1
        plt.plot(times[:i - 1], line[1:i], label=line[0], marker="o")
    plt.xlabel("Input size")
    plt.ylabel("Time (ms)")
    plt.title("Run time of different sort algorithms")
    # current_values = plt.gca().get_xticks()
    # plt.gca().set_xticklabels(['{:.0f}'.format(x) for x in current_values])
    plt.legend()
    plt.savefig("output.png")
    plt.show()

if __name__ == "__main__":
    graph_plot()