#%matplotlib notebook --used for anaconda
from scipy import sparse
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from IPython.display import display


#numpy

x = np.array([[1,2,3],[4,5,6]]) #Array format from numpy, use numpy object
print("x:\n{}".format(x))

###############################################

#numpy diagonal of 1's

#create a 2D numpy array with a diagonal of ones, and zeroes everywhere else
eye = np.eye(4)
print("NumPy array:/n{}".format(eye))

###############################################

#scipy

#convert the numpy array to a scipy sparse matrix in CSR format
sparse_matrix = sparse.csr_matrix(eye)  #changes format to coordinates
#CSR - Compressed Sparse Row
print("\nSciPy sparse CSR matrix:\n{}".format(sparse_matrix))

###############################################

#COO format, scipy

#Coordinate format of a matrix
#fast coversion between csr and csc formats

data = np.ones(4)
row_indices = np.arange(4)
col_indices = np.arange(4)
eye_coo = sparse.coo_matrix((data, (row_indices,col_indices)))
print("COO representation:\n{}".format(eye_coo))

###############################################

#matplotlib

#generate a sequence of numbers from -10 to 10 with 100 steps in between
x = np.linspace(-10,10,100)
#create a second array using sine
y = np.sin(x)
#the plot function makes a line chart of one array against another
plt.plot(x,y,marker="x")
#plt.show() #shows graph

###############################################

#create a simple dataset of people
data = {'Name': ["John", "Anna", "Peter", "Linda"],
        'Location' : ["New York", "Paris", "Berlin", "London"],
        'Age' : [24, 13, 53, 33]
        }
data_pandas = pd.DataFrame(data)
#IPython.display #allows 'pretty printing' of data frames in jupyter notebook
display(data_pandas)

#this does a really nice job of formatting

###############################################

#another way to format the above
print("\n")

#select all rows that have an age column greater than 30
display(data_pandas[data_pandas.Age>30])

