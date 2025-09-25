# полезная ссылка
https://habr.com/ru/companies/timeweb/articles/940310/

# команды кратко
gcc main.c -o app
gcc -c main.c -o main.o
gcc main.o -o app
gcc -c -fPIC main.c -o main.o  # -fPIC что ОС сможет загрузить этот код в любое место в адресном пространстве
gcc -c -fPIC func.c -o func.o
gcc -shared func.o -o func.so  # Сделали разделяемую (динамическую) библиотеку .so, указав флаг -shared
gcc main.o func.so -o app
export LD_LIBRARY_PATH=.       # добавляем точку (то есть нашу текущий каталог, так как именно там лежит нужный для линковки func.so файл)
gcc -static main.c func.c -o app # хотим слинковать стандартную библиотеку языка C с нашей программой статически

hexdump
readelf --all a.out
ldd app                        # от каких динамических библиотек зависит наш исполняемый файл

nasm -f elf64 -o return.o return.asm
ld return.o -o return
echo $?    # последний код возврата хранится в переменной окружения $?
