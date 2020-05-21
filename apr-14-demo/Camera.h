#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
private:
    float moveSpd = 0.1f;

    float lookSpeed = .01f;    //speed at which the camera "looks" at the mouse
public:
    //Change these to private when there is time
    //angle of rotation for the camera direction
    float angle;
    
    //vector representation of cameras direction
    float lx, lz;

    //XZ position of the camera
    float x, z; 

    Camera(float x, float z, float lx, float lz, float angle);

    void ChangeAngle(float angle);

    void Move(float deltaMove);

    void MoveUp();

    void MoveDown();

    void ChangeSpeed(float spd);
    
    void SetLookSpeed(float spd);

    float GetLookSpeed();

    ~Camera();
};


#endif