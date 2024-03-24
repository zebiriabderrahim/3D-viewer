//
// Created by ABDERRAHIM ZEBIRI on 2024-03-24.
//

#include "Camera.h"

namespace v3D {

        Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
                : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
        {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
                : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
        {
            Position = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }


        glm::mat4 Camera::GetViewMatrix()
        {
            return glm::lookAt(Position, Position + Front, Up);
        }


        void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
        {
            float velocity = MovementSpeed * deltaTime;
            if (direction == CameraMovement::FORWARD)
                Position += Front * velocity;
            if (direction == CameraMovement::BACKWARD)
                Position -= Front * velocity;
            if (direction == CameraMovement::LEFT)
                Position -= Right * velocity;
            if (direction == CameraMovement::RIGHT)
                Position += Right * velocity;
        }


        void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
        {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;

            Yaw   += xoffset;
            Pitch += yoffset;

            if (constrainPitch)
            {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }

            updateCameraVectors();
        }

    void Camera::ProcessMouseScroll(float yoffset) {
            Zoom -= yoffset;
            Zoom = glm::clamp(Zoom, 1.0f, 45.0f);
    }


    void Camera::updateCameraVectors() {
        float yawRadians = glm::radians(Yaw);
        float pitchRadians = glm::radians(Pitch);

        glm::vec3 front;
        front.x = cos(yawRadians) * cos(pitchRadians);
        front.y = sin(pitchRadians);
        front.z = sin(yawRadians) * cos(pitchRadians);
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }

} // v3D