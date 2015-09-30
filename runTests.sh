#!/bin/bash

echo "r=run 1-n d=details of n"
read com

if [ $com = "r" ]; then
	read num
	for i in $(seq 1 $num)
	do
		make test$i
		./test$i > tests/output$1.txt
		diff tests/output$i.txt tests/result$i.txt > /dev/null
		if test "$?" -ne 0; then
			echo "test $i failed"
		fi
	done
fi

if [ $com = "d" ]; then
	read i
	make test$i
	./test$i > tests/output$i.txt
	diff tests/output$i.txt tests/result$i.txt -y | cat -e
	if test "$?" -ne 0; then
		echo "test $i failed"
	else
		echo "test passed"
	fi
fi	
