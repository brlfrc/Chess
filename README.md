# Chess
Arduino chess project.

Under each position of the board there is a Reed switch. In each piece there is a neodymium magnet that open the switch when the piece is on a box.
So I know the pieces' position on the board and I want to delovelope a Arduino's program to plot the game.

In firsr-second-third version: to resolve the problem of taking an other piece, I consider a double scan of the board. First without the enemy's piece, then moving the own piece.


The next idea is to create a input of this type: Event 1: Off piece A --> Event 2 (optional): Off B piece taken ---> Event 3: A in the new position and bottom time empty the buffer.