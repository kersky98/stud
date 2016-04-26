cd ..\..\..\..\..\
if not exist studbuild md studbuild
cd studbuild
if not exist 61 md 61
cd 61
if not exist os md os
cd os
if not exist HoarsMonitor md HoarsMonitor
cd HoarsMonitor
if not exist win md win
cd win

cmake ..\..\..\..\..\stud\61\os\HoarsMonitor\project

pause