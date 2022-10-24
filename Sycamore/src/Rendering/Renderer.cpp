#include"Renderer.h"

#include"BatchRenderer.h"

#include"../ECS/GameObject.h"


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

void Renderer::Add(GameObject* go) {
	if (batch->HasRoom())
		batch->Add(go);
}

void Renderer::Delete(GameObject* go) {
	batch->Delete(go);
}

