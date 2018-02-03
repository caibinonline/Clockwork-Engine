#pragma once
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
#include <iostream>



#if CLOCKWORK_DEBUG == 1
#define LOG(message) std::cout<<message;
#else 
#define LOG(message) 
#endif


#define 	CLOCKWORK_RELEASE   0

#define 	CLOCKWORK_PRESS   1

#define 	CLOCKWORK_REPEAT   2


#define 	CLOCKWORK_KEY_UNKNOWN   -1

#define 	CLOCKWORK_KEY_SPACE   32

#define 	CLOCKWORK_KEY_APOSTROPHE   39 /* ' */

#define 	CLOCKWORK_KEY_COMMA   44 /* , */

#define 	CLOCKWORK_KEY_MINUS   45 /* - */

#define 	CLOCKWORK_KEY_PERIOD   46 /* . */

#define 	CLOCKWORK_KEY_SLASH   47 /* / */

#define 	CLOCKWORK_KEY_0   48

#define 	CLOCKWORK_KEY_1   49

#define 	CLOCKWORK_KEY_2   50

#define 	CLOCKWORK_KEY_3   51

#define 	CLOCKWORK_KEY_4   52

#define 	CLOCKWORK_KEY_5   53

#define 	CLOCKWORK_KEY_6   54

#define 	CLOCKWORK_KEY_7   55

#define 	CLOCKWORK_KEY_8   56

#define 	CLOCKWORK_KEY_9   57

#define 	CLOCKWORK_KEY_SEMICOLON   59 /* ; */

#define 	CLOCKWORK_KEY_EQUAL   61 /* = */

#define 	CLOCKWORK_KEY_A   65

#define 	CLOCKWORK_KEY_B   66

#define 	CLOCKWORK_KEY_C   67

#define 	CLOCKWORK_KEY_D   68

#define 	CLOCKWORK_KEY_E   69

#define 	CLOCKWORK_KEY_F   70

#define 	CLOCKWORK_KEY_G   71

#define 	CLOCKWORK_KEY_H   72

#define 	CLOCKWORK_KEY_I   73

#define 	CLOCKWORK_KEY_J   74

#define 	CLOCKWORK_KEY_K   75

#define 	CLOCKWORK_KEY_L   76

#define 	CLOCKWORK_KEY_M   77

#define 	CLOCKWORK_KEY_N   78

#define 	CLOCKWORK_KEY_O   79

#define 	CLOCKWORK_KEY_P   80

#define 	CLOCKWORK_KEY_Q   81

#define 	CLOCKWORK_KEY_R   82

#define 	CLOCKWORK_KEY_S   83

#define 	CLOCKWORK_KEY_T   84

#define 	CLOCKWORK_KEY_U   85

#define 	CLOCKWORK_KEY_V   86

#define 	CLOCKWORK_KEY_W   87

#define 	CLOCKWORK_KEY_X   88

#define 	CLOCKWORK_KEY_Y   89

#define 	CLOCKWORK_KEY_Z   90

#define 	CLOCKWORK_KEY_LEFT_BRACKET   91 /* [ */

#define 	CLOCKWORK_KEY_BACKSLASH   92 /* \ */

#define 	CLOCKWORK_KEY_RIGHT_BRACKET   93 /* ] */

#define 	CLOCKWORK_KEY_GRAVE_ACCENT   96 /* ` */

#define 	CLOCKWORK_KEY_WORLD_1   161 /* non-US #1 */

#define 	CLOCKWORK_KEY_WORLD_2   162 /* non-US #2 */

#define 	CLOCKWORK_KEY_ESCAPE   256

#define 	CLOCKWORK_KEY_ENTER   257

#define 	CLOCKWORK_KEY_TAB   258

#define 	CLOCKWORK_KEY_BACKSPACE   259

#define 	CLOCKWORK_KEY_INSERT   260

#define 	CLOCKWORK_KEY_DELETE   261

#define 	CLOCKWORK_KEY_RIGHT   262

#define 	CLOCKWORK_KEY_LEFT   263

#define 	CLOCKWORK_KEY_DOWN   264

#define 	CLOCKWORK_KEY_UP   265

#define 	CLOCKWORK_KEY_PAGE_UP   266

#define 	CLOCKWORK_KEY_PAGE_DOWN   267

#define 	CLOCKWORK_KEY_HOME   268

#define 	CLOCKWORK_KEY_END   269

#define 	CLOCKWORK_KEY_CAPS_LOCK   280

#define 	CLOCKWORK_KEY_SCROLL_LOCK   281

#define 	CLOCKWORK_KEY_NUM_LOCK   282

#define 	CLOCKWORK_KEY_PRINT_SCREEN   283

#define 	CLOCKWORK_KEY_PAUSE   284

#define 	CLOCKWORK_KEY_F1   290

#define 	CLOCKWORK_KEY_F2   291

#define 	CLOCKWORK_KEY_F3   292

#define 	CLOCKWORK_KEY_F4   293

#define 	CLOCKWORK_KEY_F5   294

#define 	CLOCKWORK_KEY_F6   295

#define 	CLOCKWORK_KEY_F7   296

#define 	CLOCKWORK_KEY_F8   297

#define 	CLOCKWORK_KEY_F9   298

#define 	CLOCKWORK_KEY_F10   299

#define 	CLOCKWORK_KEY_F11   300

#define 	CLOCKWORK_KEY_F12   301

#define 	CLOCKWORK_KEY_F13   302

#define 	CLOCKWORK_KEY_F14   303

#define 	CLOCKWORK_KEY_F15   304

#define 	CLOCKWORK_KEY_F16   305

#define 	CLOCKWORK_KEY_F17   306

#define 	CLOCKWORK_KEY_F18   307

#define 	CLOCKWORK_KEY_F19   308

#define 	CLOCKWORK_KEY_F20   309

#define 	CLOCKWORK_KEY_F21   310

#define 	CLOCKWORK_KEY_F22   311

#define 	CLOCKWORK_KEY_F23   312

#define 	CLOCKWORK_KEY_F24   313

#define 	CLOCKWORK_KEY_F25   314

#define 	CLOCKWORK_KEY_KP_0   320

#define 	CLOCKWORK_KEY_KP_1   321

#define 	CLOCKWORK_KEY_KP_2   322

#define 	CLOCKWORK_KEY_KP_3   323

#define 	CLOCKWORK_KEY_KP_4   324

#define 	CLOCKWORK_KEY_KP_5   325

#define 	CLOCKWORK_KEY_KP_6   326

#define 	CLOCKWORK_KEY_KP_7   327

#define 	CLOCKWORK_KEY_KP_8   328

#define 	CLOCKWORK_KEY_KP_9   329

#define 	CLOCKWORK_KEY_KP_DECIMAL   330

#define 	CLOCKWORK_KEY_KP_DIVIDE   331

#define 	CLOCKWORK_KEY_KP_MULTIPLY   332

#define 	CLOCKWORK_KEY_KP_SUBTRACT   333

#define 	CLOCKWORK_KEY_KP_ADD   334

#define 	CLOCKWORK_KEY_KP_ENTER   335

#define 	CLOCKWORK_KEY_KP_EQUAL   336

#define 	CLOCKWORK_KEY_LEFT_SHIFT   340

#define 	CLOCKWORK_KEY_LEFT_CONTROL   341

#define 	CLOCKWORK_KEY_LEFT_ALT   342

#define 	CLOCKWORK_KEY_LEFT_SUPER   343

#define 	CLOCKWORK_KEY_RIGHT_SHIFT   344

#define 	CLOCKWORK_KEY_RIGHT_CONTROL   345

#define 	CLOCKWORK_KEY_RIGHT_ALT   346

#define 	CLOCKWORK_KEY_RIGHT_SUPER   347

#define 	CLOCKWORK_KEY_MENU   348

#define 	CLOCKWORK_KEY_LAST   CLOCKWORK_KEY_MENU

#define 	CLOCKWORK_MOUSE_BUTTON_1   0

#define 	CLOCKWORK_MOUSE_BUTTON_2   1

#define 	CLOCKWORK_MOUSE_BUTTON_3   2

#define 	CLOCKWORK_MOUSE_BUTTON_4   3

#define 	CLOCKWORK_MOUSE_BUTTON_5   4

#define 	CLOCKWORK_MOUSE_BUTTON_6   5

#define 	CLOCKWORK_MOUSE_BUTTON_7   6

#define 	CLOCKWORK_MOUSE_BUTTON_8   7

#define 	CLOCKWORK_MOUSE_BUTTON_LAST   CLOCKWORK_MOUSE_BUTTON_8

#define 	CLOCKWORK_MOUSE_BUTTON_LEFT   CLOCKWORK_MOUSE_BUTTON_1

#define 	CLOCKWORK_MOUSE_BUTTON_RIGHT   CLOCKWORK_MOUSE_BUTTON_2

#define 	CLOCKWORK_MOUSE_BUTTON_MIDDLE   CLOCKWORK_MOUSE_BUTTON_3

#define 	CLOCKWORK_MOD_SHIFT   0x0001

#define 	CLOCKWORK_MOD_CONTROL   0x0002

#define 	CLOCKWORK_MOD_ALT   0x0004

#define 	CLOCKWORK_MOD_SUPER   0x0008