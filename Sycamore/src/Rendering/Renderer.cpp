#include"Renderer.h"

#include"BatchRenderer.h"

#include"../ECS/GameObject.h"

#include"../Utils/Logger.h"

void Renderer::ChangeBGColor(color4 color) const {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, color.a);
}

Renderer::Renderer() {
	batch = new BatchRenderer();
}

/* this is wrong. Fix it...maybe */
void Renderer::Render() {
	if (batch->HasRoom())
		batch->Render();
}

void Renderer::Add(GameObject& go) {
	if (batch->HasRoom())
		batch->Add(go);
}

void Renderer::RenderDebug(GameObject& go) {
	LOGGER_WARNING("Rendering an object for debugging purpuses");
	batch->RenderDebug(go);
}
