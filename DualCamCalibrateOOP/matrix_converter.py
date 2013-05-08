myfile = open('image.txt', 'r')
modifiedFile = open('image2.txt', 'w')

count = 0 
for line in myfile:
    line = line.strip('\n')
    line = line.strip(' ')
    line = line.strip('\r')
    linw = line.strip('')
    arr = line.split(',')
    #print arr
    for item in arr:
        item = item.strip(',')
        item = item.strip('\n')
        item = item.strip(' ')
        
        if item != '':
            modifiedFile.write(item)
            modifiedFile.write(',')
            count = count + 1
            if count % 3 == 0:
                modifiedFile.write('\n')
                count = 0;



myfile.close()
modifiedFile.close()
