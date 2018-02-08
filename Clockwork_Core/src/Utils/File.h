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
#include "Helper.h"
#include <string>


#include <fstream>//später nur in cpp und hier noch sachen anpassen
#include <sstream>



namespace clockwork {
	namespace utils {

		class File
		{

		private:
			std::string m_data;
			std::string m_filepath;

		public:
			/**/
			File() noexcept
			{

			}

			/**/
			File(const std::string& filepath) noexcept
			{
				m_filepath = filepath;
			}


		public:
			/**/
			File& read() noexcept
			{
				m_data = static_cast< std::stringstream const& >( std::stringstream() << std::ifstream(m_filepath).rdbuf() ).str();
				return *this;
			}

			/**/
			File& write() noexcept
			{
				return *this;
			}

		public:
			/**/
			const std::string& getData() const noexcept{return m_data;}

		};

	}
}