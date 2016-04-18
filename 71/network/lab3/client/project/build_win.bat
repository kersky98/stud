cd ..\..\..\..\..\..\
if not exist studbuild md studbuild
cd studbuild
if not exist 71 md 71
cd 71
if not exist network md network
cd network
if not exist lab3 md lab3
cd lab3
if not exist client md client
cd client
if not exist win md win
cd win

cmake ..\..\..\..\..\..\stud\71\network\lab3\client\project

pause