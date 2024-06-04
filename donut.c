#include <stdio.h>
#include <math.h>
#define pi M_PI

// width/height of the output "window"
const int output_width = 300;
const int output_height = 200;

const float theta_inc = 0.07;
const float phi_inc = 0.02;

const float r1 = 5; // size of donut hole
const float r2 = 2; // thickness of donut cross sections

void render(){
    char arr[output_width][output_height];
    for (float phi = 0; phi < (2*pi); phi+=phi_inc){
        for (float theta = 0; theta < (2*pi); theta+=theta_inc){

        }
    }
}

int main() {
    render();
    return 0;
}
