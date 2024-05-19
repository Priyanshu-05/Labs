import numpy as np

A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
print(A)
rSum = np.sum(A, axis = 1)
print('Row Sum:', rSum)
cSum = np.sum(A, axis = 0)
print('Column Sum: ', cSum)