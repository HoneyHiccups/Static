#include "ui.h"





namespace ui 
{


    void rui(ui_vals* vals, ImFont* Top, ImFont* Bot)
	{
	
        
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("ADockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }



        static const char settingsHeader[] = { "Volume and EQ settings. If you are using speakers, you might want to bring the bass up and treble down. The default is 50." };
        static const char pitch_settings[] = { "Change pitch: by default, the pitch will be 440 for A4. This is the 'A' key on your keyboard. Shifting the pitch of A4 will change all the pitches, as if you moved a capo on your guitar. I would recommend only changing within a small range, as excessive adjustments can damage your speakers. And will mostlikly hurt your ears." };
        static const char descrrit[] = { "This is a sound-making app. The settings window is in a dockable space, so feel free to grab the tab and move it around. The main purpose of this app is to have fun making sounds and to see what it looks like. The GUI is built in Dear ImGui, and the renderer is built with OpenGL/glfw3. In addition, I used a publicly available mini library written by The One Lone Coder to interface with the sound card. I then updated it to work with 64-bit. I hope you enjoy it." };
        //static float a4_pitch = 440.0f;
        ImGui::Separator();
        ImGui::PushFont(Top);
        ImGui::Begin("Static Settings");
        ImGui::PopFont();
        ImGui::PushFont(Bot);
        //ImGui::Text(settingsHeader);
        ImGui::TextWrapped(settingsHeader);
        ImGui::SliderInt("Volume Master", &(vals->volume), 0, 100);
        ImGui::SliderInt("Treble Volume", &(vals->treb_vol), 0, 100);
        ImGui::SliderInt("Bass Volume", &(vals->bass_vol), 0, 100);
        ImGui::Separator();
        ImGui::TextWrapped(pitch_settings);
        ImGui::SliderFloat("A4 Pitch", &(vals->a4_pitch), 220.0f, 880.0f);
        ImGui::Separator();
        ImGui::TextWrapped(descrrit);
        ImGui::Separator();

        ImGui::PopFont();
        ImGui::End();
        ImGui::End();

       
	}// end of rui




}//end of namspace