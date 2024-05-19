import numpy as np
a=np.array([(3,2,9),(1,6,7)])
s=0
for i in range(a.shape[0]):
	for j in range(a.shape[1]):
		s+=a[i,j]
print(s)