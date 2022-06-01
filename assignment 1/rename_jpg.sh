day=$(date +%F) #Storing today's date into variable
echo "Today's Date: $day"
echo "-------------------"
echo "Current directory .jpg files:"
ls *.jpg #display all .jpg files

for filename in *.jpg
do
        mv $filename $day-$filename #Rename file
done
echo "-------------------"
echo "After renaming .jpg files:"
ls *.jpg
