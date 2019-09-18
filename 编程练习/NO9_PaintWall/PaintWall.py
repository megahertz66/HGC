import math

HowGallon = 0

along = float(input("请输入长:"))
wight = float(input("请输入宽:"))

allArea = along * wight
allArea = int(math.ceil(allArea))

if allArea > 360:
    HowGallon = round(allArea / 360)
else:
    HowGallon = 1

print("You will need to purchase %d gallons of"%HowGallon)
print("paint to cover %d square feet."%allArea)
