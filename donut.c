#include <stdio.h>
#include <math.h>
#include <unistd.h>
#define pi M_PI

// width/height of the output "window"
const int output_width = 100;
const int output_height = 57;

const float phi_inc = 0.02;
const float theta_inc = 0.07;

// generally should have r1 < r2 FYI.
const float r1 = 2; // thickness of donut cross sections
const float r2 = 7; // length of donut's centerpoint to any given center of donut cross section

const float k1 = 80; // "field of view"
const float k2 = 30; // depth of object (higher val = father away object is from eye)

// A and B are angles of rotation for the donut
void render(float A, float B){
    char arr[output_height][output_width];

    for(int i = 0; i < output_height; ++i){
        for(int j = 0; j < output_width; ++j){
            arr[i][j] = ' ';
        }
    }

    for (float phi = 0; phi < (2*pi); phi+=phi_inc){
        for (float theta = 0; theta < (2*pi); theta+=theta_inc){
            // pre-calculated sin/cos values of interest for efficiency
            float sintheta = sin(theta);
            float costheta = cos(theta);
            float sinphi = sin(phi);
            float cosphi = cos(phi);
            float sinA = sin(A);
            float cosA = cos(A);
            float sinB = sin(B);
            float cosB = cos(B);

            // calculation of 2D cross section's points
            float circlex = r2 + r1*costheta;
            float circley = r1 * sintheta;

            // matrix multiplying by 3D rotation matrix, rotational extrusion (y remains unchanged because donut extrudes around y-axis)
            // also applying rotation matrices for animated rotation of entire donut
            float x = circlex * (cosB*cosphi + sinA*sinB*sinphi) - r1*cosA*sinB*sintheta;
            float y = circlex * (cosphi*sinB - cosB*sinA*sinphi) + cosA*cosB*circley;
            float z = cosA*r2 + r1*costheta*sinphi + sinA*circley;

            z += k2; // make the object further away, so eye at the origin can actually see the whole thing

            // projection of the 3D object to our 2D screen
            int xp = rintf(k1*x/(z));
            xp+= output_width/2;
            int yp = rintf(k1*y/(z));
            yp+= output_height/2;

            // discard point if it would not be in the viewing plane
            if((xp >= 0 && xp < output_width) && (yp >= 0 && yp < output_height)){
                arr[yp][xp] = 'X';
            }

            // for debugging; delete later:
            /*
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

    // print pixels to stdout
    for(int i = (output_height-1); i > 0; --i){
        for(int j = 0; j < output_width; ++j){
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
    return;
}

int main() {
    for (float a = 0; a < 8*pi ; a+=0.005){
        render(2*a,a);
        //usleep(100000);
    }
    return 0;
}
