# RImGui

## About

RImGui is a helper library designed to make implementing dear ImGui easy in your next raylib-d project.

## Example

```D
import raylib;
import bindbc.imgui;
import rimgui;

void main(){
	InitWindow(1920, 1080, "Test Program");

    // Initialize RImGui.
	rigInit();

	while (!WindowShouldClose()) {
        // Run input handling and getting delta time.
		rigRun();

		BeginDrawing();
		ClearBackground(Colors.BLACK);

        // Basic ImGui functions from bindbc.imgui.
		igNewFrame();
		igShowDemoWindow();

        // Render to the screen
		rigRender();

		EndDrawing();
	}

    // Safely exit RImGui
    rigClose();

	CloseWindow();
}


```

