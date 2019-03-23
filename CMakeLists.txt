cmake_minimum_required(VERSION 2.8.3)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(include)

set(DEPENDENCIES src/aimove/MiniMax.cpp 
            src/aimove/ScoreDifferenceEvaluationFunction.cpp
            src/controller/GameController.cpp
            src/core/BoardSquareState.cpp
            src/core/GameBoard.cpp
            src/core/Player.cpp
            src/core/HumanPlayer.cpp
            src/core/AIPlayer.cpp
            src/core/RandomHumanPlayer.cpp)

set(SOURCES src/main/Main.cpp 
            ${DEPENDENCIES})

add_executable(TicTacToe ${SOURCES})

set(TEST_SOURCES src/test/Test.cpp 
             	 ${DEPENDENCIES})

add_executable(TicTacToeTest ${TEST_SOURCES})