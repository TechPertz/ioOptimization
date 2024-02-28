First step is to run the script from codes.zip file, this will compile object for all provided c++ files.
We have 3 script file
	- compilation script file to compile all program
	- execution script file to execute all compiled code.
	- extracredit script it is to compile and execute extra credit code I.e. dd compare code and Google benchmark. 

For the execution and extra credit script you will need to change file-names accordingly.
Incase of "Permission denied issue" you can run "chmod -x <scriptname>" 

IF you want perfect file size for execution on your in reasonable time, please run 'run2' separately and change file name accordingly in executionScript.sh

In executionScript.sh and extracreditScript.sh by default filename is "ubuntu-21.04-desktop-amd64.iso". You can try changing filename or run code manually also.

Note: code compilation is "g++ -std=c++11 -O3 run.cpp -o run"

For Part - 1
	for this part we have run.cpp, and the object created via script is 'run2'.
	To perform "read" operation: ./run <file_name> -r block_size block_count
		this operation will perform read on file and generate its XOR value.
	To perform "write" operation: ./run <file_name> -w block_size block_count
		this will generate a file with file_size = block_size * block_count

For part - 2
	for this part we have run2.cpp and the object created via script is "run2"
	usage is : ./run2 <file_name>  block_size
		this operation will read the given file, and returns output as follow:
			- Time taken to read file
			- XOR value of file
			- total blocks read(block_count)

For part - 3
	for this part we have run3.cpp and the object created via script is "run3"
	usage: ./run3 <file_name> block_size
		this operation will read the given file, and returns output as follow:
			- Speed of reading in MiB/s
			- XOR value of file

For part - 4
	for this part we have same code/object from part 3, that is "run3". 
	since purpose of this part is to understand caching of disk I/O. First thing we do before every iteration is to clear cache.
	for clearing cache we run 'sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"' on our linux system. 
	steps are as follow:
	- clear cache using 'sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"'
	- then do "./run3 <file_name> block_size"
	- and after previous execution perform "./run3 <file_name> block_size" again, you will notice that speed has increased
	- we cleared cache second time and got its reading.


For part - 5
	for this par two have 2 code files, run5a.cpp and run5b.cpp and there respective objects, "run5a" and "run5b"
	"run5a" performs reading using read system call.
		usage: ./run5a <file_name> 1
	

	"run5b" performs reading using read system call.
		usage: ./run5b <file_name> 1

	"1" is default block_size for this task.

For part - 6

	to perform this task we generate a run6 object from run6.cpp file
	before running you need to check the optimal block_size for your system, in our case we used 65536.
	usage: ./fast <filename>
	



