# The step to find parser:

1. Compile modified version of valgrind. \
	`cd valgrind-3.21.0 && make`
2. Run the following command to get the call sequence. Note you should execute the program compiled with -g. Otherwise, we can not get the function name. \
	`./vg-in-place --tool=callgrind $(cmd) > info 2>&1`\
   $(cmd) is the command to execute the program with a seed input. See cmd.sh for all comannds.
3. Analyze the sequence with the APIs extracted from the ELF to get the parser function. The APIs can be extracted by invoking `extract_function_names_dynamic` in `analyze.py`. We have extracted them and put into `./APIs`. 
4. We prepare sample sequence traces in `./trace/valid` and `./trace/invalid` for trace with valid seed and invalid seed so you can type the following command to see the result:\
	`./analyze.py $product` \
	$product is the name of the target program. \
	For example, `./analyze.py giflib`, `./analyze.py libzip`, `./analyze.py xpdf` ...
