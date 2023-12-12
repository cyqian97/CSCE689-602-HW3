#!/bin/bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..

# RES_NAME="../results/res_time_nt.txt"
# cd build
# rm $RES_NAME
# cd ..

# for i in 2 3 4 5 6 7 8 9 10 11 12
# do
#     for j in 0 1 2 3 4 5
#     do
#         python3 scripts/data_generation.py 100000 50
#         cd build
#         ./main $i $RES_NAME
#         cd ..
#     done
# done

# RES_NAME="../results/res_time_nc.txt"
# cd build
# rm $RES_NAME
# cd ..

# for i in 10 20 30 40 50 60 70 80 90 100
# do
#     for j in 0 1 2 3 4 5
#     do
#         python3 scripts/data_generation.py 100000 $i
#         cd build
#         ./main 10 $RES_NAME
#         cd ..
#     done
# done

# RES_NAME="../results/res_time_np.txt"
# cd build
# rm $RES_NAME
# cd ..

# for i in 20000 40000 60000 80000 100000 120000 140000 160000 180000 200000
# do
#     for j in 0 1 2 3 4 5
#     do
#         python3 scripts/data_generation.py $i 50
#         cd build
#         ./main 10 $RES_NAME
#         cd ..
#     done
# done

# RES_NAME="../results/res_acc.txt"
# cd build
# rm $RES_NAME
# cd ..

# for i in 0 1 2 3 4 5 6 7 8 9 
# do
# python3 scripts/data_generation.py 100000 50
# cd build
# ./main 10 $RES_NAME
# cd ..
# done


# python3 scripts/data_visualization.py