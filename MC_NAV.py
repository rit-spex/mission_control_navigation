import numpy.matlib
import numpy as np

#moment_of_inertia and thruster_force control the acceleration of the vehicle
moment_of_inertia = 1
thruster_force = 0.01

#world coordinates
i_hat = np.matrix('1;0;0')
j_hat = np.matrix('0;1;0')
k_hat = np.matrix('0;0;1')

#GPIO pins for buttons
#ROLL_P = ;
#ROLL_N = ;
#PITCH_P = ;
#PITHC_N = ;
#YAW_P = ;
#YAW_N = ;

#roll = x, pitch = y, yaw = z

#initialize the axis of rotation
axis_of_rotation = np.matrix('0;0;0')

#identity matrix
I = np.matrix('1, 0, 0; 0, 1, 0; 0, 0, 1');

#initialize the normals of the faces of the vehicle
front = i_hat
right = j_hat
top = k_hat

#Rotate the ship (front, right, and top vectors) about the axis_of_rotation
#https://computergraphics.stackexchange.com/questions/2399/3d-rotation-matrix-around-vector
rotate(vector a){

    C = np.matrix('    0, -a(2),  a(1);\
                    a(2),     0, -a(0);\
                   -a(1),  a(1),     0;')

    R = I + C * 

}

switch (rotation){

    case pitch:
        axis_of_rotation += right * direction;
    break;

    case yaw:
        axis_of_rotation += top * direction;
    break;

    case roll:
        axis_of_rotation += front * direction;
    break
}
