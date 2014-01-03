#include "drawCircle.h"

void drawCircle(GLFWwindow *window,
                bool clearWindow,
                float x_min, float x_max,
                float y_min, float y_max,
                float *vertices,
                int NUM_VERTICES,
                float move_x, float move_y, float theta,
                bool drawLines)
{
        // select background color to be black
        float R = 0, G = 0, B = 0, alpha = 0;
        glClearColor(R, G, B, alpha);

        // clear all pixels in the window with the color selected above
        if(clearWindow) glClear(GL_COLOR_BUFFER_BIT);

        //------------------------------------------------------------
        // transformations on the 3D object - Modeling transformations
        //------------------------------------------------------------

        // change the current mode to MODELVIEW
        glMatrixMode(GL_MODELVIEW);

        // current transformation matrix = identity matrix
        glLoadIdentity();

        // translate the geometry along X, Y and Z
        // such that it is centered at the origin
        glTranslatef(move_x, move_y, 0.0);

        // rotate ball around the Z axis by "theta" radians
        float PI = 3.14159265358;
        glRotatef(theta*180.0/PI, 0.0, 0.0, 1.0);

        // ----------------------
        // Viewing transformation
        // ----------------------

        // change the current mode to MODELVIEW
        glMatrixMode(GL_PROJECTION);

        // current transformation matrix = identity matrix
        glLoadIdentity();

        // set clipping planes in the X-Y-Z coordinate system

        // ORTHOGRAPHIC projection
        float z_min = -20, z_max = 20.0;
        glOrtho(x_min, x_max, y_min, y_max, z_min, z_max);

        //-----------------------------------------------------------
        // Enable use of vertex data (coordinates, normals and color)
        //-----------------------------------------------------------

        // enable use of vertex coordinate information from the array
        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(3,                 // number of coordinates per vertex (X,Y,Z)
                        GL_FLOAT,          // type of numbers
                        sizeof(float)*10,  // stride - gap between each set of (X,Y,Z)
                        &vertices[0]);     // offset - location of initial (X,Y,Z)

        // enable use of vertex normal information from the array
        glEnableClientState(GL_NORMAL_ARRAY);
  
        glNormalPointer(GL_FLOAT,         // type of values
                        sizeof(float)*10, // stride - gap between each set of (N_x,N_y,N_z) 
                        &vertices[3]);    // offset - location of initial (N_x,N_y,N_z)

        // enable use of vertex color information from the array
        glEnableClientState(GL_COLOR_ARRAY);
  
        glColorPointer(4,                 // number of color values per vertex (R,G,B,A)
                       GL_FLOAT,          // type of values
                       sizeof(float)*10,  // stride - gap between each set of (R,G,B,A)
                       &vertices[6]);     // offset - location of initial (R,G,B,A)

        // increase line width
        glLineWidth(6);

        //------------------
        // draw the geometry
        //------------------
        if(drawLines) {
            // draw command
            glDrawArrays(GL_LINES,         // type of GL element
                         0,                // starting offset
                         NUM_VERTICES);    // number of vertices to be used for rendering
        }
        else {
            // draw command
            glDrawArrays(GL_TRIANGLE_FAN,  // type of GL element
                         0,                // starting offset
                         NUM_VERTICES);    // number of vertices to be used for rendering
        }
}
