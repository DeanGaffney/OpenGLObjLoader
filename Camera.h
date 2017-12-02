#pragma once
#include "Vector3.h"
#include "Model.h"

class Camera {
	public:
		Vector3 position;
		
		Camera(Vector3 position);
		void render(Model *model);
};