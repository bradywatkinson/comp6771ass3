

for i in $(seq 2 2)
do
	echo "sedding $i"
	tmp=$(sed 's/Graph.h/..\/Graph.h/' test$i.cpp)
	echo $tmp > tmp.txt
done