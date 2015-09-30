#!/bin/bash

echo "r=run 1-n d=details of n"
read com

if [ $com = "r" ]; then
	read num1
	read num2
	for i in $(seq $num1 $num2)
	do
		make test$i
		./test$i > tests/output$i.txt
		diff tests/output$i.txt tests/result$i.txt > /dev/null
		if test "$?" -ne 0; then
			echo "test $i failed"
		else
			echo "test $i passed"
		fi
	done
fi

if [ $com = "d" ]; then
	read i
	rm test$i
	make test$i
	./test$i > tests/output$i.txt
	diff tests/output$i.txt tests/result$i.txt -y | cat -e
fi	
