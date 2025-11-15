#!/bin/bash
count=$1
rm -f input your_output standard_output

echo "================== input ======================"
echo ${count} | tee input
for (( i=0; i<${count}; i++ )); do
    printf "%d.%d\n" $((($RANDOM-$RANDOM)%1000)) $RANDOM
done | tee -a input

echo "============= execution result ================"
cat input | ./script_1 | xargs printf "%.2f\n" | tee your_output

tail -n +2 input | sort -n | xargs printf "%.2f\n" > standard_output

echo "====== differences from correct result ======="
diff your_output standard_output
