
#ifndef CAMERA_H
#define CAMERA_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "vector"

enum Camera_Movement{
	FORMWARD,
	BACKWARD,
	LENT,
	RIGHT,
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5F;
const float SENSITIVTY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
   glm::vec3 Position;
   glm::vec3 Front;
   glm::vec3 Up;
   glm::vec3 Right;
   glm::vec3 WorldUp;

   float Yaw;
   float Pitch;
   float MovementSpeed;
   float MouseSensitivity;
   float Zoom;
   Camera();
   virtual ~Camera();

   void CameraCreate(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

   void CameraCreate(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
 
   
   glm::mat4 GetViewMatrix();  // 返回视图矩阵使用了 欧拉角 和 look At 矩阵

   void Processkeyboard(Camera_Movement direction,float delaTime); // 接收键盘输入定位相机

   void ProcessMouseMent(float xoffset, float yoffset, GLboolean constrainPitch = true); // 接收鼠标输入 计算偏移值 x 和 y

   void ProcessMouseScroll(float yoffset); // 接收鼠标滚轮 ，输入 纵轴 ：y

private:

	void updataCameraVectors(); // 计算相机更新
};

#endif