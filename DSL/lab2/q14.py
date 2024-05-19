import pandas as pd   

data = {"Name":["KSI","Deji","Harry"],"Height":["181cm","162cm","188cm"],"Qualification":["BTECH","MTech","MBA"]}

df = pd.DataFrame(data)

l = ["Delhi","Manipal","Hyderabad"]

df.insert(len(df),'Address',l)

print(df.head())