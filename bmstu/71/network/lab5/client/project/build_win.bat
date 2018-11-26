cd ..\..\..\..\..\..\
if not exist studbuild md studbuild
cd studbuild
if not exist 71 md 71
cd 71
if not exist network md network
cd network
if not exist lab5 md lab5
cd lab5
if not exist client md client
cd client
if not exist win md win
cd win

cmake ..\..\..\..\..\..\stud\71\network\lab5\client\project

pause