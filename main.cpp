#include "main.h"

// state variables tied to keyboard input
bool running = true;
bool pause = false;

const float R = .50;   // base circle
const float r = R/2;     // rolling circle

// keyboard input callback function
static void key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods)
{
    // quit application when the user presses ESC
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        running = false;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // pause application when user presses SPACEBAR and keeps
    // it pressed
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        pause = true;
    }

    // continue running the application when the user releases
    // the SPACEBAR
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        pause = false;
    }
}

// entry point
int main(int argc, char *argv[])  
{
    //------------------------------------------
    // create a vertex array based on facet data
    //------------------------------------------

    // vertices on the perimeter

    const int N1 = 100;  // base circle
    const int N2 = 100;  // rolling circle
///   const int N3 = 4;  // marker circle

    float* verticesBaseCircle    = new float[(N1+2)*10];  // baseline circle
    float* verticesRollingCircle = new float[(N2+2)*10];  // rolling circle
//    float* verticesMarkerCircle  = new float[(N3+2)*10];  // marker circle

    createVertexArray(N1, R,    verticesBaseCircle,    true);
    createVertexArray(N2, r,    verticesRollingCircle, true);
//    createVertexArray(N3, r/20, verticesMarkerCircle,  false);

    //--------------------------------
    //   Create a WINDOW using GLFW
    //--------------------------------
    GLFWwindow *window;

    // initialize the library
    if(!glfwInit())
    {
        return -1;
    }

    // window size for displaying graphics
    int WIDTH  = 600;
    int HEIGHT = 600;

    // set screen coordinates for display based on aspect ratio
    float x_min = - R - 2*fabs(r) - fabs(r);
    float x_max =   R + 2*fabs(r) + fabs(r);
    float y_min = (float) HEIGHT * x_min / (float) WIDTH;
    float y_max = (float) HEIGHT * x_max / (float) WIDTH;

    // set the window's display mode
    window = glfwCreateWindow(WIDTH, HEIGHT, "Rolling Circle", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
	    return -1;
    }

    // make the windows context current
    glfwMakeContextCurrent(window);

    // register the keyboard input callback function defined at the top
    glfwSetKeyCallback(window, key_callback);

//  // create a Vertex Buffer Object (VBO) and bind the vertex array to it
//  // makes rendering faster because data is copied to GPU memory
//  GLuint bufferID;
//  glGenBuffers(1, &bufferID);
//  glBindBuffer(GL_ARRAY_BUFFER, bufferID);
//  glBufferData(GL_ARRAY_BUFFER,(N+2)*10*sizeof(GLfloat),verticesRollingCircle,GL_STATIC_DRAW);

    // initialize animation parameters 
    int frame = 0;

    float roll_distance = 0.0, d_roll_distance = 0.0075; 

    float PI = 3.1415926;

    bool clearWindow = true;

    while(running)
    {
        // calculate new position of the rolling ball
        if(!pause) roll_distance += d_roll_distance;
      
        // calculate total angle by which the rolling circle should rotate
        float theta = roll_distance*(1.0/r + 1.0/R);
        float theta_new = (roll_distance + d_roll_distance)*(1.0/r + 1.0/R);

        // detect and print number of complete rotations
        float numRotations = theta * 180.0 / (PI*360);
        float numRotations_new = theta_new * 180.0 / (PI*360);
        int L1 = (int)numRotations;
        int L2 = (int)numRotations_new;
        if(L1 != L2) std::cout << "Number of rotations = " << L2 << std::endl;

        // center coordinates of the rolling circle
        float move_x = (R + r)*cos(roll_distance/R);
        float move_y = (R + r)*sin(roll_distance/R);

        // render the fixed circle
        drawCircle(window, clearWindow, x_min, x_max, y_min, y_max,
                     verticesBaseCircle, (N1+2),
                     0.0, 0.0, 0.0, true);

        // swap front and back buffers
        glfwSwapBuffers(window);

        // render the rolling circle
        drawCircle(window, clearWindow, x_min, x_max, y_min, y_max,
                     verticesRollingCircle, (N2+2),
                     move_x, move_y, theta, true);

        // swap front and back buffers
        glfwSwapBuffers(window);
/*
        // render the marker circle

        float pencil = r;

        drawCircle(window, clearWindow, x_min, x_max, y_min, y_max,
                     verticesMarkerCircle, (N3+2),
                     move_x + pencil * cos(theta), move_y + pencil * sin(theta), theta, false);

        // swap front and back buffers
        glfwSwapBuffers(window);
*/
        // poll for and processs events
        glfwPollEvents();

//      if (clearWindow == true) clearWindow = false;
    }

    // free memory
    delete[] verticesBaseCircle;
    delete[] verticesRollingCircle;
//  delete[] verticesMarkerCircle;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;    // main program is successful
}
