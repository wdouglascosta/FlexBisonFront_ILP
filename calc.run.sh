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

if [[ -n $1 && $1 == clean ]]; then

#   system_info
    rm -rf *.o calc.lex.c calc.tab.* calc

  
else
    rm -rf *.o calc.lex.c calc.tab.* calc
    gcc -c -g dataStruct.c -o dataStruct.o

    flex -o calc.lex.c calc.l
    bison -d calc.y 
    gcc -c -g calc.lex.c -o calc.lex.o

    gcc -g -o calc  calc.lex.o calc.tab.c -lfl -lm 
fi