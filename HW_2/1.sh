#!/bin/bash

##
# BASH скрипт проверяющий:
# - Использование памяти (объем свободной и используемой памяти)
# - Загрузка процессора (текущеее времени безотказной работы компьютера, количество пользователей и среднюю загрузку системы за последние 1, 5 и 15 минут)
# - Количество TCP-подключений
# - Версию ядра
##


if [ -n "$1" ]; then #  Проверка является ли первый аргумент ($1), переданный скрипту, непустым
    server_name=$1  # Сохранение значения параметра в переменную server_name
else
    server_name=$(hostname) # Присвоения выходных данных команды hostname переменной server_name
fi

function memory_check() {  # Определение функции memory_check
    echo ""  # Печать строки в консоль
	echo "Memory usage on ${server_name} is: "  # Печать строки содержащей переменную server_name в консоль
	free -h  # Отображение объема свободной и используемой памяти в системе в удобочитаемом формате.
	echo ""  # Печать строки в консоль
}

function cpu_check() {
    echo ""  # Печать строки в консоль
	echo "CPU load on ${server_name} is: "  # Печать строки содержащей переменную server_name в консоль
    echo ""   # Печать строки в консоль
	uptime  # Показ текущего времени безотказной работы компьютера, количество пользователей и среднюю загрузку системы за последние 1, 5 и 15 минут.
    echo ""   
}

function tcp_check() {  # Определение функции tcp_check()
    echo ""  
	echo "TCP connections on ${server_name}: "
    echo ""
	cat  /proc/net/tcp | wc -l  # Подсчет количества строк в файле /proc/net/tcp, которое представляет количество TCP-подключений.
    echo ""
}

function kernel_check() { # Определение функции kernel_check()
    echo ""
	echo "Kernel version on ${server_name} is: "  
	echo ""
	uname -r  # Отображение версии ядра системы.
    echo ""
}

function all_checks() { # Определение функции all_checks
	memory_check  # вызов функции memory_check
	cpu_check      # вызов функции cpu_check
	tcp_check      # вызов функции tcp_check 
	kernel_check   # вызов функции kernel_check 
}

all_checks # вызов функции all_checks