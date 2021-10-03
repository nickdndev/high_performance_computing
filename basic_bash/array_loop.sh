#!/bin/bash

array=( A B C D E F G H I K L M N O P Q R S T V X Y Z )
for i in "${array[@]}"
do
	echo "item: $i"
done