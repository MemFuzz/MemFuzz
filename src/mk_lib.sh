if [ "$#" -lt 1 ] 
then
    echo "Input ELF file path"
    exit 1
fi

if [ ! -f "$1" ]
then
    echo "Invalid file path"
    exit 1
fi

./parse_elf.py "$1"
if [ "$?" -ne 0 ]
then
    echo "Parse failed"
    exit 1
fi

rm -rf build
cp -r src build
cp memfuzz_* build 
cd build 
make static || exit 1
mkdir include lib
cp *.h include
cp *.a lib
