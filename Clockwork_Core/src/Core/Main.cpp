/*************************************************************************
* Clockwork Engine
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
#include "src\Core\ExampleGame.h"
#include "OpenAl\al.h"
#include "OpenAl\alc.h" 


int main()
{
	clockwork::engine = new clockwork::Engine("Clockwork Engine");
	clockwork::engine->start();
	delete clockwork::engine;
	
	system("pause");
	return 1;
}