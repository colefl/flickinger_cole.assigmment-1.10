# flickinger_cole.assigmment-1.10

This will be my personal project for cs3270

Gravity and Elastic Collision Simulator:
This program simulates gravity between objects with the added ability for the balls ot collide with one another.
The collision is elastic in nature which means it bounces accurately to how two circles would in a 2d plane in would if there was no
air friction and they were in an enclosed space.

How to Run This:
If in VSCode, look towards the bottom left for the build button, click that. Then click the play button. If you'd rather use terminal, inside the terminal, type

"cmake --build build"

cd into the build and enter

'./hello_window'

The second option will be your best bet if you would like to add your own parameters. which are as follows,

inside of the call in the command line enter the following:
"./hello_window <number of balls> <minimum radius of the balls> <minimum mass of the balls> " without the parenthesis

I've found that my half decade old macbook can run up to 1000 balls with radii ~1 and mass ~1 pretty smoothly so if you can get it to work for yours thats sweet.

How it works:
For the OpenGL side, which I am still wishy washy on, I use a triangle fan with an iterator to determine the number of attributes/triangles inside of the circle.
This is not manipulatable without changing the actual code and rebuilding but the number of triangles in the circle is hardcoded to 30. This isn't moved via the
matrix manipulation or anything fancy likat that, there is just a draw funciton that intakes the circles x and y which are manipulated by the code.
The gravity itself isn't so bad, it took longer for me to figure out how to make a circle fan to be honest. For this, we calculate the Force which is just
gravity \* the masses of the two objects multiplied by each other divided by the distance between the two objects squared. I still had my physics notebook for this
one so no source.
For the elastic collision I was not so lucky to have learnt this already. if the distance between the two circles is greater than their radii added together, they
they've collided. In order to calculate the velocities in which they are flying off at:
First we need to calculate the normal vector of the current position. From here we need to find the unit vector of this normal vector and via that the tangent vector.
The normal unit vector can be thought of of the perpendicular direction to where the ball is moving whilst the tangential vector is the direction which the ball is
"curving" to in it's trajectory. From this, we plug the velocity of the balls into a formula for 1D movement(because we're going to put this on a line anyways) in order
to find the new velocity accordingly with the masses of the balls and the initial velocities of either during the collision. From here, we take the dot product of the
tangential vector and the normalized unit vector before multiply the found velocities by this newly found vector which finally gives up the velocities in each direction
after the collision.
That was a lot so I will cite the source I used for this: https://www.vobarian.com/collisions/2dcollisions2.pdf I spent way too long not knowing about how I was supposed
to input the velocities into the 1D equation and not the positions.

Additionally, this is my first attempt at using OpenGL ever so the rendering may be incorrect accordingly with what I was attempting.

BUGS: When running in
