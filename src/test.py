import numpy as np
import pandas as pd
from sklearn import preprocessing
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split



data=pd.read_csv('iris.csv')
X=data.iloc[:,:-1].values
Y=data.iloc[:,-1].values

# print("--------------------------")

# print(data)
# print("--------------------------")

# print(X)
# print("--------------------------")

# print(Y)
# print("--------------------------")

print("\nMean:\n")
print(np.mean(X, axis = 0))
print("\nStandard Deviation\n")
print(np.std(X, axis = 0))
print("\n")

# StandardScaler=StandardScaler()
# X=StandardScaler.fit_transform(X)
# label_encoder=LabelEncoder()
# Y=label_encoder.fit_transform(Y)
# Y=Y.reshape(-1,1)

# # print(X)
# # print("--------------------------")

# print(Y)
# print("--------------------------")

# enc=preprocessing.OneHotEncoder()
# enc.fit(Y)
# onehotlabels=enc.transform(Y).toarray()
# Y=onehotlabels

# print(Y)
# print("--------------------------")
