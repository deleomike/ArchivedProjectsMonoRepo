import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import mglearn
import csv

TEST_PATH = "/Users/michaeldeleo/MLprojects/Assignments/Titanic/test.csv"
TRAIN_PATH = "/Users/michaeldeleo/MLprojects/Assignments/Titanic/train.csv"


##Import data sets from csv files
###numpy method
#test_set = np.loadtxt(open("test.csv","rb"), delimiter=",")

###python method
#test_set = np.array(list(csv.read(open("test.csv","rb"),delimiter=",")))

###pandas method
test_set = pd.io.parsers.read_csv(TEST_PATH,sep=',')
train_set = pd.read_csv(TRAIN_PATH)

print ("Shape of Test Data: {}".format(test_set.shape))
print ("Shape of Training Data: {}".format(train_set.shape))
#says that there are 11 things that will be used to determine survivability

print ("Test Keys: {}".format(test_set.keys()))
print ("Training Keys: {}".format(train_set.keys()))

#print ("Feature Names: {}".format(test_set.Pclass))

################################
#plot data

#use two colors one for survived and one for not
colors=['red','green']
#do not include columns passengerid and survived
#####
#set up the dataframe
plot_train_set = train_set
#init the new category
plot_train_set['Sex_int'] = np.nan
#numerize the sex so it may be plotted
plot_train_set.loc[plot_train_set['Sex']=='male' , 'Sex_int'] = 0
plot_train_set.loc[plot_train_set['Sex']=='female' , 'Sex_int'] = 1
col = plot_train_set.keys()
col = col[2:14]

titanic_dataframe = pd.DataFrame(plot_train_set, columns=col)

#set up the scatter plot
#pd.plotting.scatter_matrix(titanic_dataframe,figsize=(15,15),marker='x', c=train_set.Survived.apply(lambda x:colors[x]))
#plt.show()

################################
#build model

from scipy import sparse
from scipy.sparse import csr_matrix
from sklearn.naive_bayes import BernoulliNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split

train_set.loc[train_set['Embarked']=='Q']=0
train_set.loc[train_set['Embarked']=='C']=1
train_set.loc[train_set['Embarked']=='S']=2

nb = BernoulliNB(binarize=None)
nb.fit(plot_train_set['Sex_int'],train_set['Survived'])

train_set = sparse.csr_matrix(train_set)
#print("h{}".format(train_set.shape))

#X_train, X_test, y_train, y_test = train_test_split(train_set['Sex'],train_set['Survived'],random_state=0)
    

#knn = KNeighborsClassifier(n_neighbors = 3)

#print(knn.fit(train_set,test_set))


