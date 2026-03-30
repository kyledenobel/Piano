import matplotlib.pyplot as plt

data = []

with open("putty_log_files/putty.log") as f:
        f.readline()
        f.readline()
        for line in f:
            data.append(float(line))

plt.figure()
plt.plot(data)
plt.show()