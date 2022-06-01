#!/bin/bash
echo "---Remove Duplicate Utility---"
echo "Enter the filename: "
read filename
echo "--------------------"
if [ -e $filename ] #Checking whether file exist
then
	echo "Given File: $filename"
	if [ -s $filename ] #checking file size
	then
		echo "--> Given File Content:"
		cat $filename
		echo "--> File Content After removing duplicate lines:"
		#removing duplicate line and overwriting file
		cat -n $filename | sort -k2 | uniq -f1 | sort -k1 | cut -f2 > $filename
		cat $filename
	else
		echo "--> Given file is empty"
	fi
else
	echo "--> File does not exist"
fi
echo "---Thanks for being with us---"
