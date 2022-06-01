echo "---Delete Empty Files Utility---"
file_list="" #For storing the empty file names
echo "Empty files in current directory: "
for filename in $(ls) #iterating through all files
do
	if [ -e $filename ]
	then
		if [ ! -s $filename ]
		then
			echo $filename
			file_list="$file_list $filename" #updating file list
        	fi
	fi
done
#Giving option for deleting the files
echo "----------------------"
echo "Do you want to delete above files?(1/0)"
read option1
if [ $option1 == 1 ]
then
	for filename in $file_list
	do
		rm $filename
	done
	echo "---> All files are deleted"
fi
echo "Thanks for being with us"
