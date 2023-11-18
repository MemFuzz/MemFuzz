We use a modified AFL to cooperatte with the generator.\
The command to fuzz is:\
	`../../src/afl-2.52b/afl-fuzz -i input -o output -G /path/to/generator -S program -t 5000 -m 8G -- ${cmd}`\
For example:\
	`../../src/afl-2.52b/afl-fuzz -i ./seed/giflib -o output -G ./generator/giflib -S giflib -t 5000 -m 8G -- ./target/giffix @@`\
The ${cmd} can be found in cmd.sh\
The generator is built in ./generator\
The target program is built in ./target\
The seed is in ./seed\
To find seed generation, use "../../src/mem-seed/afl-fuzz". 
