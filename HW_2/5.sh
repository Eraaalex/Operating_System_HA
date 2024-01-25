#!/bin/bash
#  Расчет факториала числа

calculate_factorial() {
    local number=$1  # Присваивание первого аргумента функции локальной переменной number
    local factorial=1  # Присваивание переменной factorial значение 1

    while [ "$number" -ne 0 ]; do  # Цикл, выполняющийся пока number не равен 0
        factorial=$((factorial * number))  # Вычисление факториала путем умножения текущего значения factorial на number
        number=$((number - 1))  # Уменьшение number на 1
    done  # Конец цикла

    echo $factorial  # Вывод результата вычисления факториала
}

echo -n "Enter The Number: "  # Приглашение пользователю ввести число
read -r a  # Чтение с консоли введенного числа в переменную a
result=$(calculate_factorial "$a")  # Вызов функции calculate_factorial и сохранение результата в переменной result
echo "Factorial: $result"  # Вывод результата

