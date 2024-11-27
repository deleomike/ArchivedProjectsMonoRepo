import math
import numpy as np
import matplotlib.pyplot as plt

def startupCost(area, landValue, panelCost, panelArea):

    numPanels = math.floor(area / panelArea)

    totalPanelCost = numPanels * panelCost

    return totalPanelCost + landValue

def yearlyCost(landValue, taxRate):
    return landValue * taxRate

#buyback rate is in KWH
def dailyRevenue(area, avgExposure, buybackRate, panelOutput, panelArea):

    numPanels = math.floor(area / panelArea)

    #assume 8 hours of given exposure
    powerOutput = ( 8 * avgExposure * (numPanels * panelOutput) ) / 1000 #KWH

    return powerOutput * buybackRate #$

#1 acre = 45000 ft^2
acre = 45000
panelArea = 23
areas = np.linspace(1000, acre * 1, 1000)
revenue = np.array(areas)
cost = np.array(areas)

for index,area in enumerate(areas):
    revenue[index] = dailyRevenue(area, 1, 0.1, 435, panelArea) * 365

    cost[index] = startupCost(area, 10000, 100, panelArea)


fig = plt.figure()
ax = fig.add_subplot(1,1,1)
ax.plot(areas, revenue, color="tab:green")
ax.plot(areas, cost, color="tab:red")

plt.show()

print(revenue)

print(365 * revenue)

print(cost)