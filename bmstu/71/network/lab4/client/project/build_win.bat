cd ..\..\..\..\..\..\
if not exist studbuild md studbuild
cd studbuild
if not exist 71 md 71
cd 71
if not exist network md network
cd network
if not exist lab4 md lab4
cd lab4
if not exist client md client
cd client
if not exist win md win
cd win

cmake ..\..\..\..\..\..\stud\71\network\lab4\client\project

pause