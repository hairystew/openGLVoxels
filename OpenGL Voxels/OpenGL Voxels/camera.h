#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <stdlib.h>






class camera
{
public:
	glm::vec3 m_forward;
	glm::vec3 m_position;
	glm::vec3 m_up;
	float fYaw;
	float fPitch;
	glm::quat camQuat;


	camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0.f, 0.f, 1.f);
		m_up = glm::vec3(0.f, 1.f, 0.f);
		ProjMat = glm::mat4(1.0f);
		fYaw = 0.0f;
		fPitch = 0.0f;
	}

	inline glm::mat4 SetViewProjection()
	{

		glm::mat4 rot = glm::mat4(1.0f);


		glm::vec3 noVert = glm::normalize(glm::vec3(m_forward.x, 0.f, m_forward.z));
		if ((m_forward.y < -.99f && fPitch < 0 ) || ( m_forward.y > .99f && fPitch > 0))
			fPitch = 0.0f;
	
		m_forward = glm::angleAxis(fPitch, glm::cross(noVert, m_up)) * m_forward;
		m_forward = glm::angleAxis(fYaw, m_up) * m_forward;
		//std::cout  << "      m_forward: " << m_forward.x << ", " << m_forward.y << ", " << m_forward.z << std::endl;
		//move camera position in direction of forward vector
		glm::mat4 lookMatrix = (glm::lookAt(m_position, m_position + m_forward, m_up));



		ProjMat = m_perspective * lookMatrix;
		// optput Junk
		return ProjMat;
	}
	inline glm::mat4 GetViewProjection()
	{
		
		return ProjMat;

	}

	//inline glm::vec3 movePlayer

private:
	glm::mat4 ProjMat;
	
	glm::mat4 m_perspective;


};

#endif // CAMERA_H_INCLUDED

