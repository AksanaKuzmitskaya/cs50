//
// breakout.c
//
//
// Aksana Kuzmitskaya
// aksana.kuzmitskaya@gmail.com
//
// game (bounce the ball off of the paddle so as to hit bricks with it. 
// If you break all the bricks, you win! 
// But if you miss the ball three times, you lose! 
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle in pixels
#define HEIGHT_P 10
#define WIDTH_P 50

// y location of paddle
#define Y_P 550

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 12

// speed of the ball
#define PAUSE 5

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
    
    // initial velocity random along its x-axis, and constant velocity along its y-axis
    double velocity = 2.0;
    double angle = velocity * drand48();
    
    // updates scoreboard's label, keeping it centered in window
    updateScoreboard(window, label, points);
   
    // wait for click before exiting
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        updateScoreboard(window, label, points);
        
        // move ball 
        move(ball, angle, velocity);
        
        // stores return vallue of the object collided with the ball     
        GObject object = detectCollision(window, ball);
        
            
        // ball collides with the paddle and bounce off of the paddle
        if (object == paddle)
        {
            velocity = - velocity; 
        }
            
        // ball collides with the brick and removes it
        else if (object != NULL && strcmp(getType(object), "GRect") == 0)
        {
            velocity = - velocity;
            removeGWindow(window, object);
            bricks--;
            points++;
        }
         
        // game over, once bounce bottom of window 
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
        
            // number of points for scoreboard to show game over
            if ( lives == 1)
            {
                lives--;
                points = -1;
                updateScoreboard(window, label, points);
            }
            else
            {
                lives--;
                setLocation(ball, (WIDTH / 2 - RADIUS), (HEIGHT / 2 - RADIUS));
                waitForClick();
            }
        }

        // bounce off top of window
        else if (getY(ball) <= 0)
        {
             velocity = - velocity;
        }
                
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            angle = - angle; 
        }
                
        // bounce off right edge of window
        else if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            angle = - angle;
        }
        pause(PAUSE);
             
        // paddle follows the mouse movements along its x-asis
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event);
                double y = getY(paddle);
                if(x < WIDTH - WIDTH_P)
                {
                    setLocation(paddle, x, y);
                }
            }
        }                                 
    }
    
    // won
    if (bricks == 0)
    {
        updateScoreboard(window, label, points);
        return 0;
    }
    
    // game over
    waitForClick();
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // width of the brick
    int width = WIDTH / (COLS + 1);
    
    // height of the brick
    int height = width / 2;
    
    // space between bricks
    int space = width / (COLS - 1);
    
    for (int i = 0, count = 0; i < ROWS; i ++)
    {
    
        // store value for detrmination row's color
        count++;
        
        for (int j = 0; j < COLS; j ++)
        { 
            // make just three colors
            count = count % 3;
            
            // build a grid of bricks
            GRect brick = newGRect(space / 2 + j * (width + space), 2 * height + i * (height + space), width, height);
            
            // set color of the row
            setFilled(brick, true);
            if (count == 1)
            {
                setColor(brick, "GRAY");
            }
            else if (count == 2)
            {
                setColor(brick, "PINK");
            }
            else
            {
                setColor(brick, "LIGHT_GRAY");
            }
            
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval((WIDTH / 2 - RADIUS), (HEIGHT / 2 - RADIUS), 2 * RADIUS, 2 * RADIUS);
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
    GRect paddle = newGRect((WIDTH - WIDTH_P) / 2, Y_P, WIDTH_P, HEIGHT_P);
    setFilled(paddle, true);
    setColor(paddle, "DARK_GRAY");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-50");
    setColor(label, "YELLOW");
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);
    
    // won
    if (points == COLS * ROWS)
    {
        setFont(label, "SansSerif-26");
        setColor(label, "RED");
        setLabel(label, "Congratulation, You've Won!");
    }
    
    // game over
    if (points == -1)
    {
        setFont(label, "SansSerif-26");
        setColor(label, "RED");
        setLabel(label, "GAME OVER!");
    }



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
