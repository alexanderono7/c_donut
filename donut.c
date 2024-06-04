#include <stdio.h>
#include <math.h>
#define pi M_PI

// width/height of the output "window"
const int output_width = 300;
const int output_height = 200;

const float phi_inc = 0.02;
const float theta_inc = 0.07;

const float r1 = 2; // thickness of donut cross sections
const float r2 = 5; // size of donut hole

const float k1 = 0; // "field of view"
const float k2 = 20; // depth of object (higher val = father away object is from eye)

void render(){
    char arr[output_width][output_height];
    for (float phi = 0; phi < (2*pi); phi+=phi_inc){
        for (float theta = 0; theta < (2*pi); theta+=theta_inc){
            // calculation of 2D cross section's points
            float x = r2 + r1*cos(theta);
            float y = r1*sin(theta);

            // applying 3D transformation matrix (y remains unchanged because donut extrudes around y-axis)
            x = x*cos(phi);
            float z = -(r2 + r1*cos(theta))*sin(phi);
            z = z + k2; // make the object further away, so eye at the origin can actually see the whole thing
            printf("(%.2f, %.2f)\n",x,y);
        }
    }
}

int main() {
    render();
    return 0;
}
