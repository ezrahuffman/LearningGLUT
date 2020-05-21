#include "GlutApp.h"
#include "Camera.h"
#include "math.h"

Camera::Camera(float x, float z, float lx, float lz, float angle){
    this->x = x;
    this->z = z;
    this->lx = lx;
    this->lz = lz;
    this->angle = angle;
}

//add lookat function here
void Camera::ChangeAngle(float angle){
    lx = sin(angle);
    lz = -cos(angle);
    this->angle = angle;
}

void Camera::MoveUp(){
    x += lx * moveSpd;
    z += lz * moveSpd;
}

void Camera::MoveDown(){
    x -= lx * moveSpd;
    z -= lz * moveSpd;
}

void Camera::Move(float deltaMove){
    x += lx * moveSpd * deltaMove;
    z += lz * moveSpd * deltaMove;
}

void Camera::ChangeSpeed(float spd){
    this->moveSpd = spd;
}

void Camera::SetLookSpeed(float spd){
    this->lookSpeed = spd;
}

float Camera::GetLookSpeed(){
    return this->lookSpeed;
}

Camera::~Camera(){};