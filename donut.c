#include <stdio.h>
#include <math.h>
#include <unistd.h> // for sleep; delete later
#define pi M_PI

// width/height of the output "window"
const int output_width = 100;
const int output_height = 40;

const float phi_inc = 0.02;
const float theta_inc = 0.07;

// generally r1 < r2 FYI.
const float r1 = 1; // thickness of donut cross sections
const float r2 = 7; // length of donut's centerpoint to any given center of donut cross section

const float k1 = 43; // "field of view"
const float k2 = 14; // depth of object (higher val = father away object is from eye)

void render(float A, float B){
    char arr[output_height][output_width];

    for(int i = 0; i < output_height; ++i){
        for(int j = 0; j < output_width; ++j){
            arr[i][j] = ' ';
        }
    }

    for (float phi = 0; phi < (2*pi); phi+=phi_inc){
        for (float theta = 0; theta < (2*pi); theta+=theta_inc){
            // calculation of 2D cross section's points
            float x = r2 + r1*cos(theta);
            float y = r1*sin(theta);

            // matrix multiplying by 3D rotation matrix, rotational extrusion (y remains unchanged because donut extrudes around y-axis)
            x = x*cos(phi);
            float z = (r2 + r1*cos(theta))*sin(phi); // is this supposed to be negative??

            // matrix multiplying- applying rotation matrices for animated rotation of entire donut
            //x = x * (cos(B)*cos(phi) + sin(A)*sin(B)*sin(phi)) - r1*cos(A)*sin(B)*sin(theta);
            x = (r2+r1*cos(theta)) * (cos(B)*cos(phi) + sin(A)*sin(B)*sin(phi)) - r1*cos(A)*sin(B)*sin(theta);
            y = (r2+r1*cos(theta))*(cos(phi)*sin(B)-cos(B)*sin(A)*sin(phi)) + r1*cos(A)*cos(B)*sin(theta);
            z = cos(A)*(r2+r1*cos(theta))*sin(phi) + r1*sin(A)*sin(theta);

            z = z + k2; // make the object further away, so eye at the origin can actually see the whole thing

            // projection of the 3D object to our 2D screen
            int xp = rintf(k1*x/(z));
            xp+= output_width/2;
            int yp = rintf(k1*y/(z));
            yp+= output_height/2;
            arr[yp][xp] = '.';

            // for debugging; delete later:
            //*
            for(int i = (output_height-1); i > 0; --i){
                for(int j = 0; j < output_width; ++j){
                    printf("%c",arr[i][j]);
                }
                printf("\n");
            }
            //usleep(200);
            //*/

        }
    }

    for(int i = (output_height-1); i > 0; --i){
        for(int j = 0; j < output_width; ++j){
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
    return;
}

int main() {
    render(0,0);
    //for (float a = 0; a < 16*pi ; a+=0.03){
        //for (float b = 0; b < 16*pi ; b+=0.03){
        //printf("a: %f",a);
        //printf("b: %f",b);
        //}
    //}
    return 0;
}
