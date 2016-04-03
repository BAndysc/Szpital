DIRECTORY=tests
EXECUTABLE=./Hospital

PASSED=0
ALL=0
TOTAL_TIME=0

for file in $DIRECTORY/test*.in; do
    START=$(date +%s.%N)
    $EXECUTABLE -v < $file > out 2> err
    #valgrind --leak-check=full ./Hospital < $file 1>/dev/null
    END=$(date +%s.%N)
    time=$(echo "$END - $START" | bc)
    TOTAL_TIME=$(echo "$TOTAL_TIME + $time" | bc)
    if diff out "${file%.in}.out" >/dev/null 2>&1; then
    	echo "Test ${file} went ok (took $time seconds)"
        if diff err "${file%.in}.err" >/dev/null 2>&1; then
	        echo " ...and referenced string is also working"
            PASSED=$(($PASSED+1))
        else
            echo " ...but your refrenced string is broken"
        fi
    else
    	echo "Test ${file} DIDN'T go ok!"
    fi
    ALL=$(($ALL+1))
    echo ""

done

echo "Your application has passed $PASSED out of $ALL tests!"
echo "It has taken $TOTAL_TIME seconds"
