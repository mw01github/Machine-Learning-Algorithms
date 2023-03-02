import matrixmultiplication
import numpy as np

#print(testmodule.testmethod(a))
#a = np.array([[1.0, 2], [3, 4]])
#b = np.array([[4.0, 3], [2, 1]])

tempsize = 2**2

a = np.random.rand(tempsize, tempsize)
b = np.random.rand(tempsize, tempsize)

print(np.matmul(a, b))
print(matrixmultiplication.bruteforcemethod(a, b))
print(matrixmultiplication.dividemethod(a, b))