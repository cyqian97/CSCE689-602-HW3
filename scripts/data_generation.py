from  sklearn.datasets import make_blobs
import numpy as np
import os


data_name = 'data'
if(not os.path.isfile('data/' + data_name + '_points.txt')):
    n_samples = 100000
    n_centers = 10
    X, y, centers = make_blobs(n_samples=n_samples, n_features=2, centers=n_centers, cluster_std=1.0, center_box=(-10.0, 10.0), shuffle=True, random_state=1365478698, return_centers=True)

    np.savetxt('data/' + data_name + '_points.txt',X)
    np.savetxt('data/' + data_name + '_centers.txt',centers)