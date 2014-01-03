#include "createVertexArray.h"


void createVertexArray(const int N, const float R, float* vertices, bool white)
{
    // circle parameters
    const float PI = 3.1415926;

    // vertex 0
    {
        // x-y-z coordinates of the point
        vertices[ 0] = 0.0;
        vertices[ 1] = 0.0;
        vertices[ 2] = 0.0;
        // x-y-z coordinates of the normal
        vertices[ 3] = 0.0;
        vertices[ 4] = 0.0;
        vertices[ 5] = 1.0;
        // (R,G,B,A) color values 
        vertices[ 6] = white*1.0 + (1 - white)*1.0;
        vertices[ 7] = white*1.0 + (1 - white)*1.0;
        vertices[ 8] = white*1.0 + (1 - white)*0.0;
        vertices[ 9] = 1.0;
    }

    float dtheta = 2*PI/(float)N;

    // loop to create vertices on the perimeter of the circle
    int count = 10;
    for(int k = 0; k <= N; k++)
    {
        // calculate the angle
        float theta = (float)k * dtheta;

        // x-y-z coordinates of the point
        vertices[count + 0] =  R*cos(theta);
        vertices[count + 1] =  R*sin(theta);
        vertices[count + 2] =  0.0;
        // x-y-z coordinates of the normal
        vertices[count + 3] = 0.0;
        vertices[count + 4] = 0.0;
        vertices[count + 5] = 1.0;
        // (R,G,B,A) color values 
        vertices[count + 6] = white*1.0 + (1 - white) * cos(theta)*cos(theta);
        vertices[count + 7] = white*1.0 + (1 - white) * sin(20*theta)*sin(20*theta);;
        vertices[count + 8] = white*1.0 + (1 - white) * 0.0;
        vertices[count + 9] = 1.0;

        count += 10;
    }
}
