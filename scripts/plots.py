import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

sns.set()

dirname = 'results/'

# data_name = 'res_acc.txt'
# X = np.loadtxt(dirname + data_name)
# for i in range(X.shape[0]):
#     X[i,:]/=X[i,0]
# X = np.mean(X,0)
# fig, ax = plt.subplots()
# ax.set_title("$n=100000, k=50$")
# ax.bar([1,2,3],X[[0,1,3]])
# ax.errorbar([2,3],X[[1,3]],yerr=[X[[2,4]],X[[2,4]]],fmt='o', color="black")
# plt.xticks([1,2,3], ('Reference', 'k-means++', 'k-means||'))
# plt.yticks([1,1.2,1.4])
# plt.ylabel("Estimation Ratio of $\sum_{x\in X} d^2(x,C)$")
# plt.savefig("results/acc.pdf")


data_name = 'res_time_np.txt'
X = np.loadtxt(dirname + data_name)
Y = np.zeros((10,4))
for i in range(10):
    Y[i,:] = np.mean(X[i*6:i*6+5,-4:],0)
x = [20000, 40000, 60000, 80000, 100000, 120000, 140000, 160000, 180000, 200000]

fig, ax = plt.subplots()

ax.plot(x, Y[:,0], label='k-means++')
ax.fill_between(x, Y[:,0] - Y[:,1], Y[:,0] + Y[:,1], alpha=0.2)
ax.plot(x, Y[:,2], label='k-means||')
ax.fill_between(x, Y[:,2] - Y[:,3], Y[:,2] + Y[:,3], alpha=0.2)
ax.legend(loc='upper left')
ax.set_xlabel("Number of points $n$")
ax.set_ylabel("Excution time $t$(ms)")
ax.set_title("$k=50$")
plt.savefig("results/time_np.pdf")

data_name = 'res_time_nc.txt'
X = np.loadtxt(dirname + data_name)
Y = np.zeros((10,4))
for i in range(10):
    Y[i,:] = np.mean(X[i*6:i*6+5,-4:],0)
x = np.arange(10,101,10)

fig, ax = plt.subplots()

ax.plot(x, Y[:,0], label='k-means++')
ax.fill_between(x, Y[:,0] - Y[:,1], Y[:,0] + Y[:,1], alpha=0.2)
ax.plot(x, Y[:,2], label='k-means||')
ax.fill_between(x, Y[:,2] - Y[:,3], Y[:,2] + Y[:,3], alpha=0.2)
ax.legend(loc='upper left')
ax.set_xlabel("Number of centers $k$")
ax.set_ylabel("Excution time $t$(ms)")
ax.set_title("$n=100000$")
plt.savefig("results/time_nc.pdf")

data_name = 'res_time_nt.txt'
X = np.loadtxt(dirname + data_name)
Y = np.zeros((11,2))
for i in range(11):
    Y[i,:] = np.mean(X[i*6:i*6+5,-2:],0)
x = np.arange(2,13,1)

fig, ax = plt.subplots()

ax.plot(x, Y[:,0], label='k-means||')
ax.fill_between(x, Y[:,0] - Y[:,1], Y[:,0] + Y[:,1], alpha=0.2)
ax.legend(loc='upper left')
ax.set_xlabel("Number of threads $m$")
ax.set_ylabel("Excution time $t$(ms)")
ax.set_title("$n=100000, k=50$")
plt.savefig("results/time_nt.pdf")