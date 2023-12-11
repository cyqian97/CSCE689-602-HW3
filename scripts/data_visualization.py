import matplotlib.pyplot as plt
import numpy as np
from scipy.spatial import Voronoi, voronoi_plot_2d

def plot_res(dirname, data_name, ext):
    fig, ax = plt.subplots()
    X = np.loadtxt(dirname + data_name + ext + '_points.txt')
    # X = X[::100,:]
    centers = np.loadtxt(dirname + data_name + ext + '_centers.txt')
    n_clusters_ = centers.shape[0]

    dist_sq = 0.0
    for k in range(n_clusters_):
        my_members = X[:,3] == k
        cluster_center = centers[k]
        ax.plot(X[my_members, 0], X[my_members, 1],'.')
        ax.plot(
            cluster_center[0],
            cluster_center[1],
            '^',
            markersize=14,
        )
        # print("cluster size: ",np.sum(my_members))
        dist_sq += np.sum((X[my_members,:2]-centers[k,:2])**2)
        

    vor = Voronoi(centers[:,:2])
    voronoi_plot_2d(vor,ax,show_points=False, show_vertices=False)
    plt.title("$n=$%d, $\sum_{x\in X} d^2(x,C)=$ %.4e" % (X.shape[0],dist_sq))
    plt.savefig('results/res' + ext + '.jpg')

plt.figure(1)
plt.clf()

dirname = 'data/'
data_name = 'data'
plot_res(dirname, data_name, '_ref')
plot_res(dirname, data_name, '_plus')
plot_res(dirname, data_name, '_distrib')