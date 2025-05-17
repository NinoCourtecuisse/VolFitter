import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import pandas as pd

input_path = 'Data/Input/'
output_path = 'Data/Output/'
months = ["August", "November", "October", "September"]

colors = ['red', 'green', 'blue', 'cyan', 'magenta', 'yellow', 'black', 'white', 'orange', 'purple', 'pink', 'brown', 'gray', 'olive', 'teal', 'navy']
for i in range(len(months)):
    input = pd.read_csv(input_path + months[i] + '.csv')
    flat_slice = pd.read_csv(output_path + months[i] + '_flat.csv')
    sabr_slice = pd.read_csv(output_path + months[i] + '_sabr.csv')

    plt.plot(sabr_slice['Strike'], sabr_slice['IV'], color=colors[i], marker='o', markersize=5.0)
    plt.plot(flat_slice['Strike'], flat_slice['IV'], color=colors[i], marker='*', markersize=5.0)
    plt.scatter(input['Strike'], input['IV'], color='black', marker='+', s=5.0)

plt.xlabel("Strike")
plt.ylabel("IV")

plus_marker = mlines.Line2D([], [], marker='+', linestyle='None', label='market')
star_marker = mlines.Line2D([], [], marker='*', linestyle='None', label='flat')
circle_marker = mlines.Line2D([], [], marker='o', linestyle='None', label='sabr')
plt.legend(handles=[plus_marker, star_marker, circle_marker])
plt.savefig('Data/Output/slice.png')