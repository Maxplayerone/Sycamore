#include"Renderer.h"


void Renderer::ChangeBGColor(float r, float g, float b, float a) const {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}

Renderer::Renderer() {
	batch = new BatchRenderer();
}

/* this is wrong. Fix it...maybe */
void Renderer::Render() {
	if (batch->HasRoom())
		batch->Render();
}

void Renderer::Add(GameObject* go) {
	if (batch->HasRoom())
		batch->Add(go);
}

void Renderer::RenderDebug(GameObject* go) {
	LOGGER_WARNING("Rendering an object for debugging purpuses");
	batch->RenderDebug(go);
}
