import numpy as np
import matplotlib.pyplot as plt

lineSegments = np.loadtxt("./Test/visualizer_input.txt")
intersectionPoints = np.loadtxt("./Test/visualizer_output.txt")
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
# plt.grid()
# points = np.loadtxt("./Test/visualizer_output.txt")
# i = 0
# for point in points:
#     if i == 0:
#         i = 1
#         continue
#     x = [points[i-1][0], points[i-1][1]]
#     y = [point[0], point[1]]
#     X = [x[0], y[0]]
#     Y = [x[1], y[1]]
#     print(X, Y)
#     plt.plot(X, Y, 'bo', linestyle = '-')
#     i = i+1
plt.show()