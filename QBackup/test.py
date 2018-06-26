import dropbox
import sys



# We imported sys, because sys can access parameters which are given when calling the pyhton.exe with parameters; 0 is the .py file, the remaining parameters are up to the user; 
token           = sys.argv[1]
drive           = sys.argv[2]
filePath        = sys.argv[3]
backupSize      = sys.argv[4]
pathArray       = serializedPaths.split(';')



#dropbox.Dropbox verfies the user; it creates a handler with the a token; The token is created by the owner of the dropbox cloud storage; 
dbx       = dropbox.Dropbox(token)


try:

    #this 1 lines just verifies if the connection is created; If the connection is not given and exception will be thrown
    dbx.users_get_current_account()
    #print('Conntected to Dropbox')



    #Check if freespace is big enough for the backup-size
    # dbx.users_get_space_usage().used tells us how much space is used;
    # dbx.users_get_space_usage().allocation.get_individual().allocated tells us how much space is free in total (the total space of the dropbox)
    freeSpace = dbx.users_get_space_usage().allocation.get_individual().allocated - dbx.users_get_space_usage().used

    #print('Remaining freespace:',freeSpace)

    
    
except:
    #print('Unable to create a connection')
    quit(1)

    
finally:

    file = open(drive + filePath, 'r')
    pathArray = ""
    
    for line in file  
        pathArray += line + "\n"

    for file_from in pathArray:
        #Opening a file (defined before hand) with read rights
        f = open(drive + file_from,'rb')
        #print(drive + file_from)
        #this line uploads the files content to the desired destination on the dropbox; If the path of file_to contains a directory which doesnt exist, dropbox will create it
        buff = ''
        buffArr = file_from.split('\\')
        
        for i in range(0, len(buffArr)-2):
            buff += buffArr[i] + "/"

        #print("/" + buff + buffArr[len(buffArr)-1])
        dbx.files_upload(f.read(), "/" + buff + buffArr[len(buffArr)-1])
    

    #print('Completed upload of File to Dropbox\nClosing the app now!')
    # the equivalent of getchar in c/c++; Once the user hits any key the program will close; Only for testing!
    #input('Press any key to close the program')
    quit(0)

