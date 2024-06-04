#include <stdio.h>
#include <math.h>
#include <unistd.h> // for sleep; delete later
#define pi M_PI

// width/height of the output "window"
const int output_width = 100;
const int output_height = 40;

const float phi_inc = 0.02;
const float theta_inc = 0.07;

const float r1 = 1; // thickness of donut cross sections
const float r2 = 7; // size of donut hole

const float k1 = 43; // "field of view"
const float k2 = 30; // depth of object (higher val = father away object is from eye)

void render(){
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

            // applying 3D transformation matrix (y remains unchanged because donut extrudes around y-axis)
            x = x*cos(phi);
            float z = -(r2 + r1*cos(theta))*sin(phi);
            z = z + k2; // make the object further away, so eye at the origin can actually see the whole thing

            // projection of the 3D object to our 2D screen
            int xp = rintf(k1*x/(z));
            xp+= output_width/2;
            int yp = rintf(k1*y/(z));
            yp+= output_height/2;
            //yp += output_height/2;
            arr[yp][xp] = '.';

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
}

int main() {
    render();
    return 0;
}
