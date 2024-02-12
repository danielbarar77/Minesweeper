# Minesweeper

## Game Details:
- The program starts with a menu where the desired option can be selected by pressing the corresponding key:
    1. Easy - 9x9 grid with 9 mines
    2. Normal - 9x18 grid with 18 mines
    3. Hard - 9x26 grid with 27 mines
    4. Custom - the player can choose the grid size and number of mines
    5. Leaderboard - displays the top 3 players for each game mode (Easy, Normal, Hard) based on score and time
    6. How to play - displays instructions
    0. Exit - stops the program
- After each round, the scene shows the mines and flags placed correctly or incorrectly (green box for correctly placed flags and red for incorrectly placed flags)
- The scene is colored in gray, and the following colors are used for numbers of mines in nearby:
    1 - blue
    2 - green
    3 - red
    4 - violet
    5 - orange
    6 - turquoise
    7 - black
    8 - dark gray

## Instructions:
- To select a box, type the corresponding column and row (e.q. a3) and then press the ENTER key
- To place or remove a flag, type 'F' before the coordinates (e.q. Fc2)
- To win, you must place flags on all mines, but the number of flags must not exceed the number of mines
- The number in the boxes indicates how many mines are around it
- To be on the leaderboard, you need to score at least one point

## Implementation:
- Two scenes were used, the main one with hidden boxes, and a secondary one where mines and numbers are generated in the box
- The gotoXY function was used to display the boxes and text, making the game interactive
- Numerous functions were used to make the program efficient and to give a pleasant appearance to the menu
