'''
@Author: Kyle de Nobel

@brief: Testing script to visualize the notes played

@date: 3/18/2026

'''


import matplotlib.pyplot as plt

data = []
with open("piano.txt") as f:
    for line in f:
        data.append(float(line.rstrip()))



plt.figure(1)
plt.plot(data)
plt.show()