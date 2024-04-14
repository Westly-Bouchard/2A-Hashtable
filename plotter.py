import matplotlib.pyplot as plt

# Number of words in dictionary
W = 172823

# Size to draw bubbles
s = 2

# Get filename to plot
name = input("File Name to Plot: ")

# Open file
f = open("cmake-build-debug/" + name, "r")

# Create plot objects
# fig, (ax1, ax2) = plt.subplots(1, 2, sharey=True)

# Set lables
# ax1.set_xlabel("Table Size")
# ax1.set_ylabel("Performance Ratio")

# ax2.set_xlabel("Table Size")
# ax2.set_ylabel("Performance Ratio")


# Testing the use of a logarithmic scale
# ax.set_yscale("log", base=2)

# Setting axes ranges
# ax1.set(xlim=(0, W / 2), ylim=(0, 300))
# ax2.set(xlim=(0, W / 2), ylim=(0, 10))


seriesx = []
seriesy = []

# Reading data
for x in range(5):
    seriesName = f.readline()

    tempx = []
    tempy = []

    line = f.readline().strip()

    ysum = 0

    while line != "END":
        vals = line.split(",")
        tempx.append(int(vals[0]))
        tempy.append(float(vals[1]))
        ysum += float(vals[1])
        line = f.readline().strip()

    print(seriesName)
    print(ysum / 1000)

    seriesx.append(tempx)
    seriesy.append(tempy)


plt.figure(1)
plt.scatter(seriesx[0], seriesy[0], s=s)
plt.scatter(seriesx[1], seriesy[1], s=s)
plt.scatter(seriesx[3], seriesy[3], s=s)
plt.xlim([0, W / 2])
plt.ylim([0, 300])
plt.title("Table Size vs. Performance")
plt.xlabel("Table Size")
plt.ylabel("Performance Ratio")
plt.legend(["Hash0", "Hash1", "Hash3"])

plt.figure(2)
plt.scatter(seriesx[2], seriesy[2], s=s, color="red")
plt.scatter(seriesx[4], seriesy[4], s=s, color="blue")
plt.xlim([0, W / 2])
plt.ylim([0.7, 1.15])
plt.title("Table Size vs. Performance")
plt.xlabel("Table Size")
plt.ylabel("Performance Ratio")
plt.legend(["Hash2", "Hash4"])

plt.show()
