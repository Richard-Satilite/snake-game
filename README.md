# SNAKE GAME
#### A simple terminal snake game written in C programing language

# How to setup and run

The game uses [ncurses](https://man7.org/linux/man-pages/man3/ncurses.3x.html) library for terminal display. Follow these steps below to setup and run the game

#### Clone this repository

On terminal, run:

```sh
git clone git@github.com:Richard-Satilite/snake-game.git
```

And go to snake game folder

```sh
cd snake-game
```

Then generate the object file adding the [ncurses](https://man7.org/linux/man-pages/man3/ncurses.3x.html) library

```sh
gcc snake-game.c -lncurses
```

Now you can run the generated file

```sh
./a.out
```

# How to play

You use the arrow keys to control the direction of the snake's head, whose body is represented by an arrow symbol ('<', '>', '^', 'v'). Your goal is to collect as much food as possible, represented by the "@" symbol, without the snake's head colliding with the wall (represented by the "#" symbol) or its own body. There's a score counter below the game map that shows your current score.

# Game settings

In the game file (snake-game.c), you can change the symbols that represents the game elements

```c
//GAME CHARACTERS
#define SNAKE_BODY "O"
#define LEFT_SNAKE_HEAD "<"
#define RIGHT_SNAKE_HEAD ">"
#define UP_SNAKE_HEAD "^"
#define DOWN_SNAKE_HEAD "v"
#define FOOD "@"
#define BORDER "#"
```

You also can define the position of the map limits setting the (x, y) coordinates for the min and the max borders

```c
//BORDER LIMITS
#define X_MIN_BORDER 0
#define X_MAX_BORDER 41
#define Y_MIN_BORDER 0
#define Y_MAX_BORDER 41
```

## Development resources

The game was entirely developed using **C programming language** and **GNU Nano** as code editor.

<p float="left">
	<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/C_Programming_Language.svg/1853px-C_Programming_Language.svg.png" width="80" height="80" />
	<img src="https://ih1.redbubble.net/image.4813597893.3885/st,small,507x507-pad,600x600,f8f8f8.u6.jpg" width="80", height="80"/>
</p>

