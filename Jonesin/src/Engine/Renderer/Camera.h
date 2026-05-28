#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct GLFWwindow;
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
class Camera
{
public:
	// camera state
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float	  Yaw;
	float	  Pitch;
	float	  Sensitivity;;
	float	  Zoom;
	float	  Speed;
public:
	Camera(	glm::vec3 position =	DEFAULT_POSITION,
			glm::vec3 up =			DEFAULT_UP,
			float	  pitch =		DEFAULT_PITCH,
			float	  yaw	=		DEFAULT_YAW
	);
	~Camera();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(double xOffset, double yOffset);
	void ProcessMouseScroll(double xOffset, double yOffset);
	glm::mat4 GetViewMatrix();
	inline glm::mat4 GetProjection() { return m_Projection; }
	inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }

private:
	//default camera values
	glm::mat4 m_Projection;
	static constexpr glm::vec3 DEFAULT_POSITION = glm::vec3(0.0f, 0.0f, 0.0f);
	static constexpr glm::vec3 DEFAULT_UP = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr	 float DEFAULT_YAW = -90.0f;
	static constexpr	 float DEFAULT_PITCH = 0.0f;
	static constexpr	 float DEFAULT_SENSITYVITY = 0.05f;
	static constexpr	 float DEFAULT_ZOOM = 45.0f;
	static constexpr	 float DEFAULT_SPEED = 5.0f;
private:
	void updateCameraVectors();
};

