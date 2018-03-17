emcc main.cpp -O3 -s WASM=1 --llvm-lto 3 --closure 1 -o main.js
REM emcc main.cpp -s WASM=1 -o main.js