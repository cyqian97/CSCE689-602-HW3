cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..

python3 scripts/data_generation.py 100000 10
cd build
./main 10
cd ..

# for i in 1 2 3 4 5
# do
#    echo "Welcome $i times"
# done


# python3 scripts/data_visualization.py