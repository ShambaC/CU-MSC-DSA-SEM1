def sort(superlist, size, dir) :

    print("\nSuperList now: ")
    for subArrays in superlist :
        print(subArrays)

    if len(superlist) == size :
        return superlist
    
    
    newSuperList = []
    for arr in superlist :
        if dir == 0 :
            newSuperList.append([arr[0]])

            for i in range(1, len(arr)) :
                ele = arr[i]
                isAssigned = False
                for arrLists in newSuperList :
                    if ele < arrLists[0] :
                        arrLists.append(ele)
                        isAssigned = True
                        break
                if not isAssigned :
                    newSublist = [ele]
                    newSuperList.append(newSublist)
        elif dir == 1 :
            newSuperList.append([arr[-1]])

            for i in range(len(arr) - 2, -1, -1) :
                ele = arr[i]
                isAssigned = False
                for arrLists in newSuperList :
                    if ele < arrLists[0] :
                        arrLists.append(ele)
                        isAssigned = True
                        break
                if not isAssigned :
                    newSublist = [ele]
                    newSuperList.append(newSublist)
    
    return sort(newSuperList, size, abs(dir - 1))


size = int(input("Enter the number of elements: "))
originalList = []

for i in range(0, size) :
    tmp = int(input("Enter element: "))
    originalList.append(tmp)

superList = []
superList.append(originalList)

print("SieveSort: ")
sortedArray = sort(superList, size, 0)

print("Sorted array")
for ele in sortedArray :
    print(ele)