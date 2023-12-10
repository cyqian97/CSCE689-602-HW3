import matplotlib.pyplot as plt
import numpy as np

def plot_res(dirname, data_name, ext):
    plt.figure(1)
    plt.clf()
    X = np.loadtxt(dirname + data_name + ext + '_points.txt')
    centers = np.loadtxt(dirname + data_name + ext + '_centers.txt')
    n_clusters_ = centers.shape[0]

    dist_sq = 0.0
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
        dist_sq += np.sum((X[my_members,0::1]-centers[k,0::1])**2)

    plt.title("Estimated distance square sum: %.4e" % dist_sq)
    plt.savefig('res' + ext + '.jpg')

plt.figure(1)
plt.clf()

dirname = 'data/'
data_name = 'data'
plot_res(dirname, data_name, '_ref')
plot_res(dirname, data_name, '_plus')