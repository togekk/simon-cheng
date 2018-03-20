emcc main.cpp -O3 --llvm-lto 3 --closure 1 --bind -std=c++11 -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s WASM=1 -o main.js
REM emcc main.cpp --bind -std=c++11 -s WASM=1 -o main.js
REM emcc main.cpp -O3 --bind -std=c++11 -s WASM=1 -s EMTERPRETIFY=1 -s EMTERPRETIFY_FILE="'main.binary'" -s EMTERPRETIFY_ASYNC=1 --pre-js pre.js -o main.js
REM emcc main.cpp -O3 --bind -std=c++11 -s WASM=1 -s EMTERPRETIFY=1 -s EMTERPRETIFY_FILE="'main.binary'" -s EMTERPRETIFY_ASYNC=1 --pre-js pre.js --closure 1 -o main.js && parcel build index.html --public-url ./ && copy main.wasm dist && copy main.binary dist