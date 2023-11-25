# Tic Tac Toe Game

## Introduction
This is a simple implementation of the Tic Tac Toe game in C. The game allows two players to play against each other or against the computer. It also includes features to view game results and save game history to a CSV file.

## How to Play
1. Compile the code using a C compiler.
2. Run the compiled executable.
3. Follow the on-screen menu to choose an option:
   - **1. Play against a friend:** Two players take turns making moves.
   - **2. Play against the computer:** Play against the computer.
   - **3. View game results:** View the results of previous games.
   - **4. Save game history to CSV:** Save the game history to a CSV file.
   - **5. View game results from CSV:** View game results from a CSV file.
   - **6. Search game history by player name:** Search for games played by a specific player.
   - **7. Exit:** Exit the program.

## Implementation Details
- The game is played on a 3x3 grid.
- Players take turns marking positions on the board.
- The first player to get three of their marks in a row (horizontally, vertically, or diagonally) wins the game.
- If all positions on the board are filled and no player has won, the game ends in a draw.

## Note
This implementation assumes that the input provided by the players is valid and within the specified range. It does not include error handling for invalid input.

## Game History
The program maintains a game history, including player names, winners, rounds played, and date and time. You can view this history, save it to a CSV file, and load it from a CSV file.

## Contributors
This game was created and developed by the TACTYCAM Team and LuXeVi1.

Feel free to explore and enjoy playing Tic Tac Toe!
