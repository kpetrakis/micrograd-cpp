import matplotlib.pyplot as plt
from sklearn.datasets import make_moons
import numpy as np

"""
Downloads make_moons dataset
"""
if __name__ == "__main__":
  X, y = make_moons(n_samples=100, noise=0.1)
  y = y*2 -1 # make y be -1 or 1

  # visualize
  plt.figure(figsize=(5,5))
  plt.scatter(X[:,0], X[:,1], c=y, s=20, cmap='jet')
  plt.show()

  # print(X)
  # print(y)

  # write x
  with open("./dataset/data", "wb") as f:
    # f.write(np.array2string(X))
    f.write(X.astype(np.float32).data)

  # write y
  with open("./dataset/labels", "wb") as f:
    f.write(y.astype(np.float32).data)
