import datetime


currAge = int( input("What is your current age? :") )
retireAge = int( input("At what age would you like to retire? :") )

print("You have %d years left until you can retire.\n"%(retireAge - currAge))

nowYear = datetime.datetime.now().year
retireYear = nowYear+(retireAge - currAge)
if retireYear >= 0:
	print("It's %d, so you can retire in %d.\n"%(nowYear, retireYear))
else:
	print("you already go retire!\n")


