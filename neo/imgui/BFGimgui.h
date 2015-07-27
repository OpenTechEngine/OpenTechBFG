
#ifndef NEO_IMGUI_BFGIMGUI_H_
#define NEO_IMGUI_BFGIMGUI_H_

#include "../../libs/imgui/imgui.h"

// add custom functions for imgui
namespace ImGui
{

bool DragXYZ( const char* label, float v[3], float v_speed = 1.0f,
			  float v_min = 0.0f, float v_max = 0.0f,
			  const char* display_format = "%.1f",
			  float power = 1.0f, bool ignoreLabelWidth = true );
			  
bool DragXYZfitLabel( const char* label, float v[3], float v_speed = 1.0f,
					  float v_min = 0.0f, float v_max = 0.0f,
					  const char* display_format = "%.1f", float power = 1.0f );
					  
} //namespace ImGui

#endif /* NEO_IMGUI_BFGIMGUI_H_ */
