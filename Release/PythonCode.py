import re
import string



def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def displayItems(): #display Items purchased on given day
    f = open("CS210_Project_Three_Input_File.txt", "r")

    itemDict = {}
    for item in f:
        tempItem = item.strip('\n')
        if tempItem not in itemDict:
            itemDict[tempItem] = 0
        itemDict[tempItem] += 1

    for x in itemDict:
        print(f'{x}: {itemDict[x]}')

    f.close()

def displaySpecificItem(v): #How many times was specific item purchased 
    f = open("CS210_Project_Three_Input_File.txt", "r")

    itemDict = {}
    for item in f:
        tempItem = item.strip('\n')
        if tempItem not in itemDict:
            itemDict[tempItem] = 0
        itemDict[tempItem] += 1
    f.close()

    try:
        return itemDict[v]
    except:
        print("Sorry, that item does not exit")
        return

def createFrequencyFile():
    f = open("CS210_Project_Three_Input_File.txt", "r")

    itemDict = {}
    for item in f:
        tempItem = item.strip('\n')
        if tempItem not in itemDict:
            itemDict[tempItem] = 0
        itemDict[tempItem] += 1
    f.close()

    f = open("frequency.dat", "w")
    for x in itemDict:
        f.write(f'{x} {itemDict[x]} \n')
    f.close()

    



    
