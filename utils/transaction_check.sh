#!/bin/bash

PWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

pattern=algos_*.dat
solution=solution1

csim=$(find $PWD/../solution1/csim/build/ -name $pattern)
wrapc=$(find $PWD/../solution1/sim/wrapc/ -name $pattern)
wrapc_pc=$(find $PWD/../solution1/csim/build/ -name $pattern)

# Count number of failed comparisons
errors=0

# Pretty comparison result couting errors
function show_result
{
    if [ $1 == 0 ]; then
      echo "> success."
    else
      echo "> failed."
      ((errors++))
    fi
}

echo "> csim=$csim"
echo "> wrapc=$wrapc"
echo "> wrapc_pc=$wrapc_pc"

echo "> comparing csim <> wrapc ..."
diff -u $csim $wrapc
show_result $?

echo "> comparing csim <> wrapc_pc ..."
diff -u $csim $wrapc_pc
show_result $?

echo "> comparing wrapc <> wrapc_pc ..."
diff -u $wrapc $wrapc_pc
show_result $?

# return number of failed comparisons
exit $errors
