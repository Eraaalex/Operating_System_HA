#!/bin/bash
# Построчное чтение введенного файла и вывод в консоль содержимого 

 echo "Enter a filename:"
read filename    # считывание имени файла в переменную filename


read_file() {
    local file=$1
    while read line; do  # чтение строки из файла пока не окончание файла
        echo $line  # Вывод строки в консоль
    done < $file   # Завершение цикла while, чтение из файла
}

read_file "$filename"