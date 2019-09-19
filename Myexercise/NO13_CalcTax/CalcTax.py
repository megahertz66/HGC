"""
What is the order amount? 10
What is the state? WI
The subtotal is $10.00.
The tax is $0.55.
The total is $10.55.
"""

amount = float(input("What is the order amount? :"))
state = input("What is the state? :")
state = state.upper()
tax = 1
if ("WI" == state) or ("Wisconsin" == state):
    tax = 1.055

print("The tax is %.02f."%(tax-1))
print("The total is %.02f."%(amount * tax))
