rm main
g++ c_map.cpp -c -o map.o

g++ c_map1.cpp -c -o map1.o

g++ c_robot.cpp -c -o robot.o

g++ input.cpp -c -o input.o

g++ main.cpp -c -o main.o

g++ output_process.cpp -c -o  output_process.o

g++ output.cpp -c -o output.o

g++ process_control.cpp -c -o process_control.o

g++ robot_table_control.cpp -c -o robot_table_control.o

g++ value_hash.cpp -c -o hash.o

g++ main.o map.o map1.o robot.o input.o output_process.o output.o process_control.o robot_table_control.o hash.o -g -o main

rm *.o
rm outlog.txt
chmod 777 main
./Robot -d -m 1.txt "main">>outlog.txt
