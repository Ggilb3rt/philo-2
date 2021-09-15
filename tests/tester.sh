#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
LGRAY='\033[;37m'
LBLUE='\033[1;34m'
PURP='\033[0;35m'
NC='\033[0m'

printf "\033[0;33mEmpty \n\033[0m"
./philo 

printf "\033[0;35mTest re er as i\n\033[0m"
./philo re er as i

printf "\033[0;33m\nTest basic 7 42 10 3 \n\033[0m"
./philo 7 42 10 3


printf "\033[0;33m\nTest basic 4 42 10 3 9\n\033[0m"
./philo 4 42 10 3 9


printf "\033[0;33m\nTest overflow 4000000000000000 4 5 6 4444\n\033[0m"
./philo 4000000000000000 4 5 6 4444