To note:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Paramaeters used : <mazefile.txt><Players_name><score.csv>
if non parameters given or the wrong amount is given game still starts but with hardwritten <maze.txt><Uknown Player><score.csv>
Collission with a wall is also considered a move
For reasons i'm not sure at all one of the two NPCs sometimes teleports (i guess magic?)
Score is being read from a score.csv file
Space apparently end the game as if ESC was pressed
Maze3.txt is just a large maze i found. Don't try play it on that.
Scroll appears also in the beginning instead of using a load condition of getting all 10 gems first 
so player can opt-in and go for that but with a lower score at the end.
Esc/winning/losing will still keep track of your score (how many gems you managed to gather) and add it to the csv file and scoreboard respectivlly.
In case erros at compilation from Dev-cpp we need to reset the inc directory and lib directory for ncurses provided on folder.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
