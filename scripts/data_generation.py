from  sklearn.datasets import make_blobs
import numpy as np
import os
import sys

def gen_data(argv):
    data_name = 'data'
    # if(not os.path.isfile('data/' + data_name + '_points.txt')):
    n_samples = int(argv[0])
    n_centers = int(argv[1])
    cluster_std=1.0
    # n_samples = 1000000
    # n_centers = 100
    # cluster_std=0.2
    X, y, centers = make_blobs(n_samples=n_samples, n_features=2, centers=n_centers, cluster_std=cluster_std, center_box=(-10.0, 10.0), shuffle=True, return_centers=True)
    #random_state=1365478698,

    np.savetxt('data/' + data_name + '_points.txt',X)
    np.savetxt('data/' + data_name + '_centers.txt',centers)

if __name__ == "__main__":
    gen_data(sys.argv[1:])