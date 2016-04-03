#!/bin/bash

PASSED=0
ALL=0
TOTAL_TIME=0
DEBUG_CHECK=0
PARAMETERS=

OK=$'\e[32;01m [OK]\e[0m'
WRONG=$'\e[31;01m [WRONG]\e[0m'

ILLEGAL_ARGUMENTS="Usage: ./test.sh [-v (optional]) [prog] [tests directory]"
EXECUTABLE_DOESNT_EXIST="Executable file does not exist"
TESTS_DOESNT_EXIST="Test directory does not exist"


if [ $# == 3 ]; then
    DEBUG_CHECK=1
    PARAMETERS="-v"
    EXECUTABLE=$2
    DIRECTORY=$3
elif [ $# == 2 ]; then
    EXECUTABLE=$1
    DIRECTORY=$2
else
    echo $ILLEGAL_ARGUMENTS
    exit 0
fi



if [ -f $EXECUTABLE ]; then
    EXECUTABLE="./$EXECUTABLE"
else
    echo $EXECUTABLE_DOESNT_EXIST
    exit 0
fi

if [ ! -d $DIRECTORY ]; then
    echo $TESTS_DOESNT_EXIST
    exit 0
fi


for file in $DIRECTORY/test*.in; do
    FILENAME=${file/$DIRECTORY/""}
    START=$(date +%s.%N)
    $EXECUTABLE $PARAMETERS < $file > out 2> err
    #valgrind --leak-check=full ./Hospital < $file 1>/dev/null
    END=$(date +%s.%N)
    time=$(echo "$END - $START" | bc)
    TOTAL_TIME=$(echo "$TOTAL_TIME + $time" | bc)
    if diff out "${file%.in}.out" >/dev/null 2>&1; then
    	echo "Test ${FILENAME} $OK (took $time seconds)"
        if [ $DEBUG_CHECK == 1 ]; then
            if diff err "${file%.in}.err" >/dev/null 2>&1; then
	            echo " ...referenced string $OK"
                PASSED=$(($PASSED+1))
            else
                echo " ...but refrenced string $WRONG"
            fi
            echo ""
        fi
    else
    	echo "Test ${FILENAME} $WRONG"
    fi
    ALL=$(($ALL+1))
done

echo "Your application has passed $PASSED out of $ALL tests!"
echo "It has taken $TOTAL_TIME seconds"
