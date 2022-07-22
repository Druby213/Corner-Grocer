import re
import string


def printsomething():
    print("Hello from python!")


def PrintMe(v):
    print("You sent me: " + v)
    return 100


def SquareValue(v):
    return v * v


# open and sort input file returning dict of each item and number of times it was sold
def uniqueItems():

    # Variable declaration/initialization
    uniqueList = []  
    itemCount = {} 

    # open inputFile.txt as read and close automatically when we are done with it
    with open("/home/dylan/CLionProjects/projectThree/inputFile.txt", 'r') as file:
        contents = file.read().split('\n')  # seperate the values of the file by line and store as a list

    # iterate through contents
    for i in contents:
        # if the value of the current index is not in uniqueList add it to uniqueList
        if i not in uniqueList: 
            uniqueList.append(i)  

    uniqueList.sort()  # sort unique list alphabetically

    # iterate through uniqueList counting the number of times it appears in contents
    # then add the uniquList value and number counted to itemCount dict (Key : value) = (uniqueList : count)
    for i in range(len(uniqueList)):
        itemCount[uniqueList[i]] = contents.count(uniqueList[i])

    return itemCount  # return itemCount dict holding the item name and number of times it has been sold


# print each item and the amount sold
def itemsSold():

    # Variable declaration/initialization
    itemCount = uniqueItems()  

    print(f"{'*' * 26}\n {'ITEMS SOLD':^26} \n{'-' * 26}")  # display header for the items sold

    # print the key and the value for each key:value pair in itemCount
    for itemName, itemNum in itemCount.items():
        print(f"{itemName.title()}: {itemNum}")
    print('\n')


# check for a specific item sold based on user input
def itemLookup(v):

    # Variable declaration/initialization
    itemCount = uniqueItems()

    # if the entered item is listed in itemCount print the name of the item and amount sold
    if v in itemCount:
        print(f"\n{v}: {itemCount[v]}\n")
    # if the item is not in itemCount let the user know it is not listed
    else:
        print(f"\n{v} is not on the list.\n")

    return 0


# save the dict of items and number of times sold to frequency.dat
def saveFile():

    # Variable declaration/initialization
    itemCount = uniqueItems()

    # open frequency.dat and write each item name and count on its own line
    # if the file does not exist it will be created automatically
    with open("/home/dylan/CLionProjects/projectThree/frequency.dat", 'w') as write_file:

        for itemName, itemNum in itemCount.items():
            write_file.write(f"{itemName.title()} {itemNum}\n")
