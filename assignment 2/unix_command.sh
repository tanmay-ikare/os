#!/bin/bash
while [ true ]
do
echo -e "\n\n---Explore UNIX---"
echo -e "1) Content of Current directory \n2) Current Working Directory \n3) Read existing file"
echo -e "4) Edit/Create file \n5) Today's Date \n6) See Manual of command \n7) Exit"
echo -e "\n--> Enter Choice: "
read option1
echo "---------------------"
case $option1 in
        1) echo "Content of current directory:"
                ls
                ;;
        2) echo "Current Working Directory:"
                pwd
                ;;
        3) echo "Read Existing file:"
                echo -e "\n--> Enter filename: "
                read filename
                echo "Content of file:"
                cat $filename
                ;;
        4) echo "Edit/Create file:"
                echo -e "\n--> Enter filename: "
                read filename
                vim $filename
                ;;
        5) echo "Today's Date:"
                date
                ;;
        6) echo "See Manual of command:"
                echo -e "\n--> Enter Command: "
                read commands
                man $commands
		 ;;
	7) echo "---Thank you being with us---"
	        break
esac
done
