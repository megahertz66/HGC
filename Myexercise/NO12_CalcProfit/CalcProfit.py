# TODO: 如果不输入则会报错

principal = float(input("Enter the principal :"))

while True:
    rate =  float(input("Enter the rate of interest :"))
    if rate < 1:
        print("请输入百分比，像15而不是0.15")
        continue
    break

years = float(input("Enter the number of years :"))

worth = principal*(1 + rate / 100  * years)


print("After %d years at %.02f, the investment will be worth $%.01f"%(years, rate, worth))
