import matrixmultiplication
import numpy as np

#print(testmodule.testmethod(a))
#a = np.array([[1.0, 2], [3, 4]])
#b = np.array([[4.0, 3], [2, 1]])


tempsize = 2**4

np.random.seed(2)
a = np.random.randint(50, size=(tempsize, tempsize)).astype('float64')
b = np.random.randint(50, size=(tempsize, tempsize)).astype('float64')

print(np.matmul(a, b))
print("\n")
print(matrixmultiplication.bruteforcemethod(a, b))
print("\n")
print(matrixmultiplication.dividemethod(a, b))
print("\n")
print((matrixmultiplication.dividemethod(a, b) - matrixmultiplication.strassenmethod(a, b)))
