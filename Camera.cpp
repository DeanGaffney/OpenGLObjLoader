#include "Camera.h"

Camera::Camera(Vector3 position) {
	this->position = position;
}

void Camera::render(Model *model) {
	model->render();
}