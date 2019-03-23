Implementation of tic tac toe board game in C++

Software requirements: 
cmake 2.8.3 (minimum)
g++ 5.4.0

To build the source : 

To launch game:

1. Clone repository.

2. Open command prompt.

3. Navigate to the folder where you have cloned the repository on local.

4. To build your project run the following in root folder of the repository:

	$ cmake -H. -Bbuild
	$ cmake --build build -- -j3
	
   The first command will create CMake configuration files inside folder /build and the second one will generate two executables TicTactToe and TicTacToeTest in /bin folder inside the root folder of the repository.

5. To run the game can do :
	$ ./bin/TicTacToe

	This will give you the start menu for the game from where you can choose different options and will be able to play the game.

6. To run the unit tests for the game do :
	$ ./bin/TicTacToeTest
