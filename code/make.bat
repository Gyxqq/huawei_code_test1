del main.exe
g++ c_map.cpp -c -o map.o
timeout /T 2
g++ c_map1.cpp -c -o map1.o
timeout /T 2
g++ c_robot.cpp -c -o robot.o
timeout /T 2
g++ input.cpp -c -o input.o
timeout /T 2
g++ main.cpp -c -o main.o
timeout /T 2
g++ output_process.cpp -c -o  output_process.o
timeout /T 2
g++ output.cpp -c -o output.o
timeout /T 2
g++ process_control.cpp -c -o process_control.o
timeout /T 2
g++ robot_table_control.cpp -c -o robot_table_control.o
timeout /T 2
g++ value_hash.cpp -c -o hash.o
timeout /T 2
g++ main.o map.o map1.o robot.o input.o output_process.o output.o process_control.o robot_table_control.o hash.o -g -o main.exe
timeout /T 2
del *.o
del outlog.txt
Robot.exe -d -m 1.txt "main.exe">outlog.txt
timeout /T 200