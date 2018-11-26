cd ..\..\..\..\..\
if not exist studbuild md studbuild
cd studbuild
if not exist 71 md 71
cd 71
if not exist asm md asm
cd asm
if not exist factor md factor
cd factor
if not exist win md win
cd win

cmake ..\..\..\..\..\stud\71\asm\factor\project

pause