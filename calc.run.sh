#!/usr/bin/env bash

system_info()
{
    echo ""
    echo "*******************************************"
    echo ""
    echo "WILLIAM COSTA - RA89239"

   

} 

# while getopts ":i:g:c:" opt; do
#   case $opt in
#     i) IND="$OPTARG"
#     ;;
#     g) GER="$OPTARG"
#     ;;
#     c) CRO="$OPTARG"
#     ;;
#     -h) system_info
#     ;;
#     \?) echo "Invalid option -$OPTARG" >&3
#     ;;
#   esac
# done

[[ -n $IND ]] || IND=20
[[ -n $GER ]] || GER=3
[[ -n $CRO ]] || CRO=50

if [[ -n $1 && $1 == -h ]]; then

  system_info
else
    gcc -c dataStruct.c -o dataStruct.o


    flex  -o calc.lex.c calc.l
    bison -d calc.y 
    gcc -c calc.lex.c -o calc.lex.o

    gcc -o calc calc.lex.o calc.tab.c -lfl -lm 
fi