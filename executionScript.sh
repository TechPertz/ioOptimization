# File name change it if needed
FILENAME="ubuntu-21.04-desktop-amd64.iso" 


# Running the programs
echo "Running Part 1... run"
echo "full file reading"
./run $FILENAME -r  512 8000000
./run $FILENAME -r 1024 4000000
./run ubuntu-21.04-desktop-amd64.iso -r  512 8000000

echo
echo "\nReading by changing block size and blockcount"
./run $FILENAME -r 512 1000
./run $FILENAME -r 1024 500

echo
echo "\nWriting new file"
./run write1 -w 1024 1000
./run 1mbtest.txt -w 1024 1000
./run 4mbtest.txt -w 1024 4000
./run 8mbtest.txt -w 1024 8000
./run 16mbtest.txt -w 1024 16000



echo
echo "\nreading new file"
./run write1 -r 1024 1000
./run write1 -r 512 2000


echo
echo  "\nRunning Part 2..."
./run2 $FILENAME 1024
echo
./run2 $FILENAME 2048
echo
./run2 $FILENAME 4092
echo
./run2 $FILENAME 8192
echo
./run2 $FILENAME 16384
echo
./run2 $FILENAME 65536


echo
echo  "\nRunning Part 3..."
./run3 $FILENAME 1024
echo
./run3 $FILENAME 2048
echo
./run3 $FILENAME 4092
echo
./run3 $FILENAME 8192
echo
./run3 $FILENAME 16384
echo
./run3 $FILENAME 65536

echo  "\n\nmake sure you have correct file name inside script before running part4.\nmake sure this script is running on linux system\nIn the script we are using linux cache clearing command"
# You can change file name like this
FILENAME="ubuntu-21.04-desktop-amd64.iso" 

echo  "\nRunning Part 4..."
sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\nRunning after cache is cleared" 
./run3 $FILENAME 1024
echo  "\nnext immediate run"
./run3 $FILENAME 1024
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 1024

sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\n\nRunning after cache is cleared" 
./run3 $FILENAME 2048
echo  "\nnext immediate run"
./run3 $FILENAME 2048
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 2048

sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\n\nRunning after cache is cleared" 
./run3 $FILENAME 4096
echo  "\nnext immediate run"
./run3 $FILENAME 4096
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 4096

sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\n\nRunning after cache is cleared" 
./run3 $FILENAME 8192
echo  "\nnext immediate run"
./run3 $FILENAME 8192
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 8192

sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\n\nRunning after cache is cleared" 
./run3 $FILENAME 16384
echo  "\nnext immediate run"
./run3 $FILENAME 16384
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 16384

sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\n\nRunning after cache is cleared" 
./run3 $FILENAME 32768
echo  "\nnext immediate run"
./run3 $FILENAME 32768
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 32768

sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\n\nRunning after cache is cleared" 
./run3 $FILENAME 65536
echo  "\nnext immediate run"
./run3 $FILENAME 65536
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 65536


sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo  "\n\nRunning after cache is cleared" 
./run3 $FILENAME 131072
echo  "\nnext immediate run"
./run3 $FILENAME 131072
echo  "\nThird run after cache is cleared again"
./run3 $FILENAME 131072

echo  "\nmake sure you have the correct file name inside the script before running part5"
echo  "To make the task easy, here we have already added the files used for testing:\n - 1mbtest.txt\n - 4mbtest.txt\n - 8mbtest.txt\n - 16mbtest.txt"

mb1file="1mbtest.txt" 
mb4file="4mbtest.txt" 
mb8file="8mbtest.txt" 
mb16file="16mbtest.txt" 

echo  "\n\nRunning Part 5..."
echo  "\nRunning'run5a' 1mb file - READ"
./run5a $mb1file 1
echo  "\nRunning'run5b' 1mb file - lseek"
./run5b $mb1file 1

echo  "\nRunning 'run5a' 4mb file - READ"
./run5a $mb4file 1
echo  "\nRunning'run5b' 4mb file - lseek"
./run5b $mb4file 1

echo  "\nRunning 'run5a' 8mb file - READ"
./run5a $mb8file 1
echo
echo  "\nRunning'run5b' 8mb file - lseek"
./run5b $mb8file 1
echo
echo "\nRunning 'run5a' 16mb file - READ"
./run5a $mb16file 1
echo
echo "\nRunning'run5b' 16mb file - lseek"
./run5b $mb16file 1


FILENAME="ubuntu-21.04-desktop-amd64.iso" 
echo "\nmake sure you have correct file name inside script before running part6.\ndefault filename is 'ubuntu-21.04-desktop-amd64.iso'"
echo "\n\nRunning Part 6..."
sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"
echo "\n\nRunning after cache is cleared" 
./fast $FILENAME
echo "\nNext immediate run"
./fast $FILENAME
echo "\nThird run after cache is cleared again"
./fast $FILENAME


# # Script end
echo "All parts from 1 - 6 executed."
