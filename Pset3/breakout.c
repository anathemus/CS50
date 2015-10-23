//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // random seeded variable
    double drand48(void);
    
    // ball speeds up, down, side to side is somewhat random.
    double vertical = 2.0;   
    double horizontal = 2 * drand48();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // ckecks for mouse action
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
            // if the mouse moved, grab the X value and move the paddle
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, HEIGHT/1.2);
            }
        }
        
        move(ball, horizontal, vertical);
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            // If the ball collides ith the paddle
            if (object == paddle)
            {
                vertical = -vertical;
            }
            
            // Else if the ball collides with the brick(s)
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                points++;
                updateScoreboard(window, label, points);
                vertical = -vertical;
                horizontal = -horizontal;
            }
            
        }
        
        // Top border check, bounce back if it "collides" with top border.
        else if (getY(ball) <= 0 )
        {
            vertical = -vertical;
        }
        
        /**
        *If user misses and the ball falls through the bottom. :( Lose a life and start over
        * Thank you, setLocation!
        */
        else if (getY(ball) > HEIGHT) 
        {
            lives --;
            // main();
            // GOval ball = initBall(window);
            setLocation (ball, WIDTH/2, HEIGHT/2-40);
        }
        
        // Bounce from the sides.
        else if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0 )
        {
            horizontal = -horizontal;
        }
        
        // Pausing for effect.
        pause(12);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Initiates the bricks for the game, varying color by row.
    int brickX = 2;
    int brickY = 50;
    string color[5];
    color[0] = "RED";
    color[1] = "ORANGE";
    color[2] = "YELLOW";
    color[3] = "GREEN";
    color[4] = "BLUE";
    
    for (int n = 0; n < ROWS; n++)
    {
        for (int i = 0; i < COLS; i++)
        {
            GRect brick = newGRect(brickX, brickY, 35, 15);
            setFilled(brick, true);
            add(window, brick);
            brickX += 40;
            setColor(brick, color[n]);
        }
        
        brickY += 20;
        brickX = 2;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int ballSize = 20;
    int ball_x = (WIDTH/2);
    int ball_y = (HEIGHT/2 - 40);
    
    GOval ball = newGOval(ball_x, ball_y, ballSize, ballSize); 
    setFilled(ball, true);
    setColor(ball, "DARK_GRAY");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // puts paddle in original position, defines paddle.
    int paddle_x = WIDTH/2 - (35);
    int paddle_y = HEIGHT/1.2 - (5);
    GRect paddle = newGRect(paddle_x,paddle_y,70,10);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("");
    setFont(scoreboard, "SansSerif-18");
    setLocation(scoreboard, 25, 25);
    add(window, scoreboard);
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "Points: %i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
