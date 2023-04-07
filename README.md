Welcome to Petar and Jeff's Watopoly project!
This project is an analogy to the classic Monopoly game, implemented in C++.

*Rules*
This game allows up to 8 players. Each player starts with a certain sum of money and take turns to roll the dice and travel around the board. Equipped with actions such as purchasing, auctioning, trading properties, every player can strategically spend their money and try to become the last player remaining by making other players go bankrupt. The game ends when there is only one player left standing.

*Getting Started*
To start the game, run `make` command in your terminal (make sure you are in the `..\watopolyPetarJeff` directory). You can then either load a saved game or start a new game. If you choose a saved game, the game will start immediately; if a new game is chosen, you would need to enter the number of players and their names before the game can start.

*Features*
Our version of Watopoly has the following features
- Purchase properties that others need to pay rent if they were to land on it
- Increase the tuition of an academic property by building up to 4 bathrooms and a cafeteria on it
- Mortgage and Unmortgage properties (only an unmortgaged property can be mortgaged)
- Auction when a player lands on an unowned property + forfeit their purchasing privilege
- Bankruptcy when a player's debt exceeds the total amount of money they can earn before his/her round ends, either by trading or by mortgaging all their properties.
- SLC and Needles Hall that may make you:
  - Move a certain amount of blocks forwards or backwards
  - Go to a specific location (which could be Tims)
  - Win or lose a certain sum of money
- If you go to Tims, you have to stay in Tims for the next 3 rounds, unless you:
  - Rolled a double during one of the rounds
  - Pay $50
  - Use a Roll Up the Rim cup

*Versions & Improvements*
To be written.