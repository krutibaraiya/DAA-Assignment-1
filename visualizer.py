import numpy as np
import matplotlib.pyplot as plt

lineSegments = np.loadtxt("input_test.txt")
intersectionPoints = np.loadtxt("output_test.txt")
plt.grid()
for ls in lineSegments:
    pointA = [ls[0], ls[1]]
    pointB = [ls[2], ls[3]]
    x = [pointA[0], pointB[0]]
    y = [pointA[1], pointB[1]]
    plt.plot(x, y, 'bo', linestyle = '-')

for ip in intersectionPoints:
    x = ip[0]
    y = ip[1]
    plt.plot(x, y, 'ro')
plt.show()