import os
import pandas as pd
import matplotlib.pyplot as plt

directory = "plots/"
os.makedirs(directory, exist_ok=True)

df = pd.read_csv("data.csv", sep=";")

columns = ["Float", "Double", "Long Double"]

for col in columns:
    fig, ax = plt.subplots() 
    
    df.plot(x="n", y=col, ax=ax)
    
    fig.savefig(os.path.join(directory, f"{col.lower().replace(' ', '_')}.png"))
    plt.close(fig) 

fig, ax = plt.subplots()
df.plot(x="n", ax=ax)
fig.savefig(os.path.join(directory, "all.png"))
plt.close(fig)
