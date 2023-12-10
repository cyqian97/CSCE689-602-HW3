import matplotlib.pyplot as plt
import numpy as np

plt.figure(1)
plt.clf()

dirname = 'data/'
data_name = 'data'
X = np.loadtxt(dirname + data_name + '_res_points.txt')
centers = np.loadtxt(dirname + data_name + '_res_centers.txt')
n_clusters_ = centers.shape[0]
print(n_clusters_)

for k in range(n_clusters_):
    my_members = X[:,3] == k
    cluster_center = centers[k]
    plt.plot(X[my_members, 0], X[my_members, 1],'.')
    plt.plot(
        cluster_center[0],
        cluster_center[1],
        '^',
        markersize=14,
    )
plt.title("Estimated number of clusters: %d" % n_clusters_)
plt.savefig("res.jpg")
plt.show()