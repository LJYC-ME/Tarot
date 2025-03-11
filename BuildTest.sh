cmake -G Ninja -S . -B Build -DCMAKE_CXX_COMPILER=/opt/homebrew/Cellar/llvm/19.1.7_1/bin/clang++
cmake --build Build --config=Debug
./Build/Tarot-Sandbox