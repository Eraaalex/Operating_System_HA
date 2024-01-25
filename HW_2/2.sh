#!/bin/bash
# Проверка файла введенного через консоль на существавание и доступа к записи

is_writable() {
    local file=$1  # Присвоение первого аргумента локальной переменной filename
    if [ -w "$file" ]; then  # Проверка доступа для записи файла с таким именем
        echo "The file is writable."
    else
        echo "The file is not writable."
    fi   # Окнончание условного оператора
}

check_file() {
    local file=$1
    if [ -f "$file" ]; then  # Проверка условия существования файла
        echo "File exists."  # вывод строки в консоль
        is_writable "$file"  # Вызов функции  is_writable с параметром
    else
        echo "File does not exist."  
        return 1   # возврат из функции 1
    fi    # Окнончание условного оператора
}


while true; do  # начало цикла 
    echo "Enter a filename:"  
    read filename    # считывание имени файла в переменную filename

    if check_file "$filename"; then # Проверка условия при вызове функции check_file с параметром  "$filename"
        break  # Выход из цикла
    else
        echo "Try again." # вывод строки в консоль
    fi
done
