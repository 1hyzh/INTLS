#pragma once

#include <memory>
#include "JNI.h"
#include "Hooks.h"
class Globals final
{
public:
	bool rcDelay = false;
	bool autoclick = false;
	int autoClickDelay = 40;

	void CancelRightClickDelay()
	{
		while (true) {
			if (rcDelay == true)
			{
				p_jni->p_cminecraft->SetRightClickDelay(0);
			}
		}
	}

};

extern Globals g_Globals;