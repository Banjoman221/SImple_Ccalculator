echo "Building..."

echo "$(uname -s)"

if [[ $(uname -s) == "Linux" ]]; then
gcc Ccalculator.c -g -o Ccalculator 
echo "Running..."
echo "Done..."
./Ccalculator
else
x86_64-w64-mingw32-gcc Ccalculator.c -o Ccalculator.exe 
echo "Running..."
echo "Done..."
./Ccalculator.exe
fi
