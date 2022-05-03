from datetime import datetime

#Global variables
userLogged = False
outView =  "loop"
total_list = []
counteItems = 0


def IOView():
    global userLogged
    global outView
    global total_list
    newList = []
    global counteItems 

    if  userLogged == False :
        name = input("Introduce tu nombre ")
        edad = input("Introduce tu edad ")
        print(f'hola {name} edad {edad}')
        userLogged = True
    else :
        gasto = input("Introduce el concepto ")
        cantidad = input("Introduce la cantidad")
        newList += [gasto]
        newList += [cantidad]
        dateItem = datetime.date(datetime.now())
        newList += [dateItem]
        #total_list.append 
        #for x in range(len(newList)):
        #    print(newList[x])
        
        counteItems =counteItems+1
        print(f'cuantos van {counteItems}')
    
    total_list.append(newList)

    if counteItems ==3 :
        for x in range(len(total_list)):
            print(total_list[x])

        outView="exit"





#def gastosController():


def printDate():
    global outView
    print(datetime.date(datetime.now()))
    print("hola")
    while outView == "loop":
        IOView()

def main():
    printDate()


main()