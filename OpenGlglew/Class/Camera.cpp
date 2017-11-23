#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{

}
Camera::~Camera()
{

}
void Camera::CameraCreate(glm::vec3 position /* = glm::vec3(0.0f , 0.0f, 0.0f)*/, glm::vec3 up /* = glm::vec3(0.0f , 1.0f, 0.0f)*/, float yaw /* = YAW */, float pitch /* = PITCH*/) 
{
	Front = (glm::vec3(0.0f, 0.0f, -1.0f));
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVTY;
	Zoom = ZOOM;
	
	Position = position;
	WorldUp = up;
	Yaw = YAW;
	Pitch = PITCH;
	updataCameraVectors();
}
void Camera::CameraCreate(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVTY;
	Zoom = ZOOM;
	 
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updataCameraVectors();
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}
void Camera::Processkeyboard(Camera_Movement direction, float delaTime)
{
	float velocity = MovementSpeed *delaTime;
	if (direction ==  FORMWARD)
	{
		Position += Front * velocity;
	}
	if (direction == BACKWARD)
	{
		Position -= Front * velocity;
	}
	if (direction == LENT)
	{
		Position -= Right * velocity;
	}
	if (direction == RIGHT)
	{
		Position += Right * velocity;
	}
}
void Camera::ProcessMouseMent(float xoffset, float yoffset, GLboolean constrainPitch /* = true */)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < - 89.0f)
		{
			Pitch = -89.0f;
		}
	}
	updataCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset)
{
    if (Zoom >= 1.0f && Zoom <= 45.0f)
    {
		Zoom -= yoffset;
    }
	if (Zoom < 1.0f)
	{
		Zoom = 1.0f;
	}
	if (Zoom > 45.0f)
	{
		Zoom = 45.0f;
	}
}
void Camera::updataCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw) *cos(glm::radians(Pitch)));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw) * cos(glm::radians(Pitch)));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

}