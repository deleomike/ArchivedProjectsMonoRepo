from sklearn.datasets import load_iris
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import mglearn
#import IPython.display import display
#from sklearn.neighbors import KNeighborsClassifier

#CONTENTS:
###############################################
#LOADING OF DATASET
#SPLITTING AND MIXING DATASET
#VISUALIZING THE DATASET
#BUILDING THE MODEL: K-NEAREST NEIGHBORS
#PREDICTING
#EVALUATING
#SUMMARY


iris_dataset = load_iris()
#the iris object returned by load_iris is a bunch object which is similar
#to a dictionary
#it contains keys and values

print("Keys of iris_dataset: \n{}".format(iris_dataset.keys()))

#the value of key DESCR is a descripion of the dataset
print(iris_dataset['DESCR'][:193]+"\n...")

#the value of the key target_names is an array of strings, containing the species
#of flower that we want to predict
print("Target names: {}".format(iris_dataset['target_names']))

#the value of feature_names is a list of strings giving the description of each feature
#feauture
print("Feature names: \n{}".format(iris_dataset['feature_names']))

#the data is contained in the target and data fields. it is a numpy array
print("Type of data: {}".format(type(iris_dataset['data'])))

#the rows in the data array correspond to flowers
#the columns represent four measurements taken for each flower
#this gets the dimensions
print("Shape of data: {}".format(iris_dataset['data'].shape))

#from this we can see 150 different flower samples

#here are the feature values for the first five samples
print("First five rows of data:\n{}".format(iris_dataset['data'][:5]))

#the target array contains species of each flower as a numpy array
print("Type of target: {}".format(type(iris_dataset['target'])))

#dimensions of target
print("Shape of target: {}".format(iris_dataset['target'].shape))

#species are encoded as integers 0->2
print("Target:\n{}".format(iris_dataset['target']))

#0: setosa
#1: versicolor
#2: virginica


###############################################
###############################################
#Question: How does one train on this data? an algorithm will simply memorize it,
# so we need to mess up the order to train it

#scitkit has a train_test_split function that will prove helpful here
#the function uses 75% of the data as the training set, and the remaining
#25% as the test set.

#notes: in scikit, data is usually denoted with X

from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(
    iris_dataset['data'], iris_dataset['target'], random_state=0)
#HOW IT WORKS:
#Before making the split, tts shuffles the datset using a pseudorandom number generator
#This is important, because if we had just takent the last 25%, we would have target 0,1
#in the learn set, and target 2 in the test set. Distribution is key

#For the book example, the random state is the same for demonstration. However,
#for the real datasets the random seed should be different each time

#X_train: 75% of data
#y_train: 75% of corresponding targets
print("X_train shape: {}".format(X_train.shape))
print("y_train shape: {}".format(y_train.shape))

#X_test: 25% of data to be predicted
#y_test: 25% of targets to be predicted
print("X_test shape: {}".format(X_test.shape))
print("y_test shape: {}".format(y_test.shape))

###############################################

#NOTE: It is often a good idea to inspect the data before building a machine learning model
#this is good practice, because you may be able to solve the problem without the
#algorithm.
#A good way to do this is to use a scatter plot, or a pair plot

#lets try it out!

#create dataframe from data in X_train
#label the columns using the strings in iris_dataset.feature_names
iris_dataframe = pd.DataFrame(X_train, columns=iris_dataset.feature_names)
#create a scatter matrix from the dataframe, color by y_train
pd.plotting.scatter_matrix(iris_dataframe, c=y_train, figsize=(15,15),
                           marker='o', hist_kwds={'bins':20},s=60,
                           alpha=0.8,cmap=mglearn.cm3)
plt.show()

#looking at the data it is clear that there is a distinction between the blue
#and all other points. However, there is a lot of overlap between the green and red
#There is seperability and from these factors we can say that a machine learning model should
#be able to seperate them

###############################################
###############################################

#Building the First Model: K-nearest neighbors

#The k in k nearest neighbors signifies that instead of using only the closest neighbor the
#new datapoint, we can consider any fixed number k of neighbors in the training (i.e. 3 or
# 5 closest neighbors)
#Then we can make a prediction using the majority class among these neighbors. There are
#more details on this in CH2, for now it will be one neighbor

from sklearn.neighbors import KNeighborsClassifier
#machine learning models in scikit-learn are implemented in their own classes which are
#called Estimator classes. The k-nearest neighbors algorithm is implemented in the
#KNeighborsClassifier class

knn = KNeighborsClassifier(n_neighbors=1)
#knn encapsulates the algorithm

print(knn.fit(X_train,y_train)) #(training)
#fit returns the knn object, and some of the parameters inside of this object
#notice that most of these are default values

###############################################

#Making Predictions

X_new = np.array([[5,2.9,1,0.2]])
#sepal length: 5cm
#sepal width: 2.9cm
#petal length: 1cm
#petal width: 0.2cm
print("X_new.shape: {}".format(X_new.shape))

#scikit-learn always expects two-dimensional arrays for the data

prediction = knn.predict(X_new)
print("Prediction: {}".format(prediction))
print("Predicted target name: {}".format(
    iris_dataset['target_names'][prediction]))
#the prediction classifies this flower as a setosa in target 0
#but how can we trust this?

###############################################

#Evaluating the model

#now we will test the prediction we made earlier. This is where the test set comes in
#It was not used to train the model, but WE know what the values should be, therefore
#We can compute the ACCURACY

y_pred = knn.predict(X_test)
print("Test set predictions:\n {}".format(y_pred))

#accuracy
print("Test set score: {:.2f}".format(np.mean(y_pred==y_test)))

#or we can use the score method for accuracy
print("Test set score: {:.2f}".format(knn.score(X_test,y_test)))


###############################################
###############################################
###############################################

#summary of code

#can be completed as such

X_train, X_test, y_train, y_test = train_test_split(
    iris_dataset['data'], iris_dataset['target'], random_state=0)
knn.KNeighborsClassifier(n_neighbors=1)
knn.fit(X_train,y_train)

print("Test set score: {:.2f}".format(knn.score(X_test,y_test)))

