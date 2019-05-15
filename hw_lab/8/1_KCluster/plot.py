import pandas as pd

import matplotlib.pyplot as plt
import numpy as np


def read_data(file_path):
    #columa_names
    column_names = ['label','x', 'y']
    data = pd.read_csv(file_path,header = None, names = column_names)
    return data

def scatter_with_color(x,y,labels,figure_no):
    plt.scatter(x,y,c=labels)
    plt.figure(figure_no)
    plt.xlabel('x values')
    plt.ylabel('y values')
    plt.title('Scatter with color')

dataset = read_data('clustering.csv')
figure_no=1
x=dataset['x']
y=dataset['y']
label=dataset['label']
scatter_with_color(x,y,label,figure_no)
plt.show()