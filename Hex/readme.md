# Hex Game

This project implements algorithms to solve various hex boards. It does not implement the game itself.

# Algorithms
The algorithms inlcude:

- Getting Board Size
- Getting pawns number
- Checking is board state is valid (enough pawns, not too much)
- Checking if game is over at its current state
- Checking if win was possible (there can be only 1 winning path)
- Minmax algorithm checking if player can win in:
   + 1 move
   + 2 moves

Sadly those minmax algorithms do not work as expected, and are slow at its current state and sometimes output wrong answer

# Testing
Test files are in ```./Tests``` folder, current test can be changed in ```Hex.cpp``` file  
Find ```ifstream ifs{ R"(.\Tests\11.in.txt)" };``` and change its value to proper test. You can compare tests and their validity with .out files, which contains valid results.