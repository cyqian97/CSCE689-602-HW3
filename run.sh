python3 scripts/data_generation.py
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./main
cd ..
python3 scripts/data_visualization.py