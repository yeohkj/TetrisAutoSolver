# TetrisAutoSolver
Implemented a tetris solver which uses Depth First Search Algorithm to find out the best possible way to place tetriminoes for the shortest possible stack given an input string of tetriminoes. Rotations included.

**Problem**

![image](https://user-images.githubusercontent.com/61396956/123648148-9ed14500-d820-11eb-9176-926af711971d.png)

The problem to solve is illustrated above. The game is an arena of width 6 and unlimited height,
with an opening at the top. Tetrominoes (shapes made from 4 squares, see figure 2), will be
presented in order and will “fall” from the top of the arena until they are supported by either the
bottom edge or other tetrominoes. Your system should determine the optimal locations to place
the tetrominoes to result in the shortest tower.

![image](https://user-images.githubusercontent.com/61396956/123648290-bc9eaa00-d820-11eb-8b2d-09883d46fbf4.png)


**Rotations**
The advanced solution allows for any 90 degree rotation of the tetrominoes.

![image](https://user-images.githubusercontent.com/61396956/123648414-d63ff180-d820-11eb-9ee5-c59411fd96e1.png)

The I, O, S, and Z tetrominoes have rotational symmetry so only have two possible orientations,
while the T, J, and L tetrominoes have four
