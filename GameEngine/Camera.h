#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>

namespace GE {
	class Camera {
	public:
		Camera(glm::vec3 camPos, glm::vec3 camTarget, glm::vec3 camUpDir, float fov, float ar, float near, float far) {
			pos = camPos;
			target = camTarget;
			up = camUpDir;

			fovy = fov;
			aspectR = ar;
			nearClip = near;
			farClip = far;

			updateCamMatrices();

			SDL_GetMouseState(&oldMouseX, &oldMouseY);
		}
		~Camera() {}

		glm::vec3 getPos() {
			return pos;
		}

		glm::vec3 getTarget() {
			return target;
		}

		glm::vec3 getUpDir() {
			return up;
		}

		glm::mat4 getViewMatrix() {
			return viewMat;
		}

		glm::mat4 getProjectionMatrix() {
			return projectionMat;
		}

		float getPitch() {
			return pitch;
		}
		float getYaw() {
			return yaw;
		}

		float getOldMouseX() {
			return oldMouseX;
		}
		float getOldMouseY() {
			return oldMouseY;
		}

		void setPosX(float x) {
			pos.x = x;

			updateCamMatrices();
		}

		void setPosY(float y) {
			pos.y = y;

			updateCamMatrices();
		}

		void setPosZ(float z) {
			pos.z = z;

			updateCamMatrices();
		}

		void setPos(float x, float y, float z) {
			pos = glm::vec3(x, y, z);

			updateCamMatrices();
		}

		void setPos(glm::vec3 newPos) {
			pos = newPos;

			updateCamMatrices();
		}

		void setTarget(glm::vec3 newTarget) {
			target = newTarget;

			updateCamMatrices();
		}

		void setUpDir(glm::vec3 newUp) {
			up = newUp;

			updateCamMatrices();
		}

		void setFov(float newFov) {
			fovy = newFov;

			updateCamMatrices();
		}

		void setAspectRatio(float newAR) {
			aspectR = newAR;

			updateCamMatrices();
		}

		void setNearClip(float newNearClip) {
			nearClip = newNearClip;

			updateCamMatrices();
		}

		void setFarClip(float newFarClip) {
			farClip = newFarClip;

			updateCamMatrices();
		}

		void setPitch(float newPitch) {
			pitch = newPitch;

			if (pitch > 70.0f) pitch = 70.0f;
			if (pitch < -70.0f) pitch = -70.0f;
		}
		void setYaw(float newYaw) {
			yaw = newYaw;
		}

		void setOldMouseX(float newOldMouseX) {
			oldMouseX = newOldMouseX;
		}
		void setOldMouseY(float newOldMouseY) {
			oldMouseY = newOldMouseY;
		}

	private:
		void updateCamMatrices() {
			viewMat = glm::lookAt(pos, pos + target, up);
			projectionMat = glm::perspective(glm::radians(fovy), aspectR, nearClip, farClip);
		}

	private:
		glm::vec3 pos;
		glm::vec3 target;
		glm::vec3 up;

		//Camera projection
		float fovy;
		float aspectR;
		float nearClip;
		float farClip;

		//Camera rotation
		float pitch = 0.0f;
		float yaw = -90.0f;

		//mouse variables
		int oldMouseX, oldMouseY;

		glm::mat4 viewMat;
		glm::mat4 projectionMat;
	};
}