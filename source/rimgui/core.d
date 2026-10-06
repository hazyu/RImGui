module rimgui.core;

import bindbc.imgui;
import raylib;

ImGuiContext * ctx;
ImGuiIO * io;
Texture2D fontTexture;

void rigInit() {
    auto ret = loadImGui();
    ctx = igCreateContext(null);
    io = igGetIO();

    io.DisplaySize = ImVec2(
        cast(float)GetScreenWidth(),
        cast(float)GetScreenHeight()
    );

    io.BackendPlatformName = "imgui_impl_raylib".ptr;
    io.BackendRendererName = "imgui_impl_raylib_renderer".ptr;

    char * pixels;
    int width, height;
    ImFontAtlas_GetTexDataAsRGBA32(io.Fonts, &pixels, &width, &height);

    Image image;
    image.data = pixels;
    image.width = width;
    image.height = height;
    image.mipmaps = 1;
    image.format = PixelFormat.PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

    fontTexture = LoadTextureFromImage(image);
    ImFontAtlas_SetTexID(io.Fonts, cast(void*)cast(size_t)fontTexture.id);

    io.KeyMap[ImGuiKey.Tab]        = KeyboardKey.KEY_TAB;
    io.KeyMap[ImGuiKey.LeftArrow]  = KeyboardKey.KEY_LEFT;
    io.KeyMap[ImGuiKey.RightArrow] = KeyboardKey.KEY_RIGHT;
    io.KeyMap[ImGuiKey.UpArrow]    = KeyboardKey.KEY_UP;
    io.KeyMap[ImGuiKey.DownArrow]  = KeyboardKey.KEY_DOWN;
    io.KeyMap[ImGuiKey.PageUp]    = KeyboardKey.KEY_PAGE_UP;
    io.KeyMap[ImGuiKey.PageDown]  = KeyboardKey.KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey.Home]      = KeyboardKey.KEY_HOME;
    io.KeyMap[ImGuiKey.End]       = KeyboardKey.KEY_END;
    io.KeyMap[ImGuiKey.Insert]    = KeyboardKey.KEY_INSERT;
    io.KeyMap[ImGuiKey.Delete]    = KeyboardKey.KEY_DELETE;
    io.KeyMap[ImGuiKey.Backspace] = KeyboardKey.KEY_BACKSPACE;
    io.KeyMap[ImGuiKey.Space]     = KeyboardKey.KEY_SPACE;
    io.KeyMap[ImGuiKey.Enter]     = KeyboardKey.KEY_ENTER;
    io.KeyMap[ImGuiKey.Escape]    = KeyboardKey.KEY_ESCAPE;
    io.KeyMap[ImGuiKey.KeypadEnter] = KeyboardKey.KEY_KP_ENTER;
    io.KeyMap[ImGuiKey.A]         = KeyboardKey.KEY_A;
    io.KeyMap[ImGuiKey.C]         = KeyboardKey.KEY_C;
    io.KeyMap[ImGuiKey.V]         = KeyboardKey.KEY_V;
    io.KeyMap[ImGuiKey.X]         = KeyboardKey.KEY_X;
    io.KeyMap[ImGuiKey.Y]         = KeyboardKey.KEY_Y;
    io.KeyMap[ImGuiKey.Z]         = KeyboardKey.KEY_Z;

}

void rigRun() {
    // Set delta time
    io.DeltaTime = GetFrameTime();

    // Mouse checks
    io.MousePos = ImVec2(
        cast(float)GetMouseX(),
        cast(float)GetMouseY()
    );
    io.MouseDown[0] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    io.MouseDown[1] = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

    Vector2 mw = GetMouseWheelMoveV();
    io.MouseWheelH += mw.x;
    io.MouseWheel += mw.y;


    // Keyboard checks
    int character = GetCharPressed();
    while (character > 0) {
        ImGuiIO_AddInputCharacter(io, cast(uint)character);
        character = GetCharPressed();
    }

    for (int i = 0; i < 512; i++) {
        io.KeysDown[i] = IsKeyDown(cast(KeyboardKey)i);
    }

    io.KeyCtrl = IsKeyDown(KeyboardKey.KEY_LEFT_CONTROL) || IsKeyDown(KeyboardKey.KEY_RIGHT_CONTROL);
    io.KeyShift = IsKeyDown(KeyboardKey.KEY_LEFT_SHIFT) || IsKeyDown(KeyboardKey.KEY_RIGHT_SHIFT);
    io.KeyAlt = IsKeyDown(KeyboardKey.KEY_LEFT_ALT) || IsKeyDown(KeyboardKey.KEY_RIGHT_ALT);
    io.KeySuper = IsKeyDown(KeyboardKey.KEY_LEFT_SUPER) || IsKeyDown(KeyboardKey.KEY_RIGHT_SUPER);

}

void rigRender() {
    igRender();
    auto drawData = igGetDrawData();
    auto defaultTexture = fontTexture; 
    if (drawData == null) return;

    for (int n = 0; n < drawData.CmdListsCount; n++) 
    {
        ImDrawList* cmdList = drawData.CmdLists[n];
        ImDrawVert* vtxBuffer = cmdList.VtxBuffer.Data;
        ImDrawIdx* idxBuffer = cmdList.IdxBuffer.Data;

        for (int cmdi = 0; cmdi < cmdList.CmdBuffer.Size; cmdi++) 
        {
            ImDrawCmd* pcmd = &cmdList.CmdBuffer.Data[cmdi];
            
            uint currentTextureId = (pcmd.TextureId != null) ? cast(uint)cast(size_t)pcmd.TextureId : defaultTexture.id;

            rlBegin(RL_TRIANGLES);
            rlSetTexture(currentTextureId);

            for (uint i = 0; i < pcmd.ElemCount; i += 3) 
            {
                uint idx0 = idxBuffer[pcmd.IdxOffset + i];
                uint idx1 = idxBuffer[pcmd.IdxOffset + i + 1];
                uint idx2 = idxBuffer[pcmd.IdxOffset + i + 2];

                ImDrawVert v0 = vtxBuffer[pcmd.VtxOffset + idx0];
                ImDrawVert v1 = vtxBuffer[pcmd.VtxOffset + idx1];
                ImDrawVert v2 = vtxBuffer[pcmd.VtxOffset + idx2];

                // Unpack color data
                Color col0 = Color(
                    cast(ubyte)(v0.col), 
                    cast(ubyte)(v0.col >> 8), 
                    cast(ubyte)(v0.col >> 16), 
                    cast(ubyte)(v0.col >> 24)
                );
                Color col1 = Color(
                    cast(ubyte)(v1.col), 
                    cast(ubyte)(v1.col >> 8), 
                    cast(ubyte)(v1.col >> 16), 
                    cast(ubyte)(v1.col >> 24)
                );
                Color col2 = Color(
                    cast(ubyte)(v2.col), 
                    cast(ubyte)(v2.col >> 8), 
                    cast(ubyte)(v2.col >> 16), 
                    cast(ubyte)(v2.col >> 24)
                );

                rlColor4ub(col0.r, col0.g, col0.b, col0.a);
                rlTexCoord2f(v0.uv.x, v0.uv.y);
                rlVertex2f(v0.pos.x, v0.pos.y);

                rlColor4ub(col2.r, col2.g, col2.b, col2.a);
                rlTexCoord2f(v2.uv.x, v2.uv.y);
                rlVertex2f(v2.pos.x, v2.pos.y);

                rlColor4ub(col1.r, col1.g, col1.b, col1.a);
                rlTexCoord2f(v1.uv.x, v1.uv.y);
                rlVertex2f(v1.pos.x, v1.pos.y);
            }

            rlEnd();
        }
    }
    rlSetTexture(0);
}

void rigEnd() {
}