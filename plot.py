import matplotlib.pyplot as plt
import pandas as pd

input = pd.read_csv('Data/Input/August.csv')
output = pd.read_csv('Data/Output/output.csv')

plt.plot(output['Strike'], output['IV'], label='model iv', color='blue')
plt.scatter(input['Strike'], input['IV'], marker='+', s=5.0, label='market iv', color='grey')
plt.xlabel("Strike")
plt.ylabel("IV")
plt.legend()
plt.savefig('Data/Output/output.png')