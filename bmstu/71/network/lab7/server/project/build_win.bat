cd ..\..\..\..\..\..\
if not exist studbuild md studbuild
cd studbuild
if not exist 71 md 71
cd 71
if not exist network md network
cd network
if not exist lab7 md lab7
cd lab7
if not exist server md server
cd server
if not exist win md win
cd win

cmake ..\..\..\..\..\..\stud\71\network\lab7\server\project

pause