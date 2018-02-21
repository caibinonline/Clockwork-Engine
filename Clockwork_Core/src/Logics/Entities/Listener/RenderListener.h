#pragma once
/*************************************************************************
* Clockwork-Engine
* A C++/Opengl/GLFW3 game engine
* Website: clock-work.tk
*------------------------------------------------------------------------
* Copyright (C) 20017-2018 Niko Miklis <clock-work@gmx.de> - All Rights Reserved
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* You can use this software under the following License: https://github.com/Clock-work/Clockwork-Engine/blob/master/LICENSE
*************************************************************************/
#include "src\Logics\Entities\GameObject.h"

namespace clockwork {
	namespace logics {
		
		class Chunk;

		class RenderListener 
			: public virtual GameObject
		{

		public:
			RenderListener() noexcept;//bei move/copy konstruktor/operator ggf nicht addrenderlistener/etc aufrufen, oder auch schon remove und renderadd zum verschieben, kopieren, etc
			~RenderListener() noexcept;

		protected:
			//muss von allen UNTERSTEN erbenden klassen im konstruktor aufgerufen werden(wegen virtual objekte müssen erstellt worden sein)
			void init() noexcept;

		public:
			//dazuschreiben: wird aufgerufen, wenn chunk des objekts in renderdistance kommt | kann somit auch ggf andere effekte abspielen | kann aber auch manuell aufgerufen werden
			virtual void renderAdd() noexcept = 0;
			virtual void renderRemove() noexcept = 0;


		};

	}
}

