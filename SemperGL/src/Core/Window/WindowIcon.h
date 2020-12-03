#pragma once
#include <iostream>


namespace SemperGL
{
	class WindowIcon
	{
	public:
		WindowIcon(const std::string &filepath);
		~WindowIcon();

		void *GetIcon() const;

	private:
		void *m_Image;
		int m_BPP;
		std::string m_Filepath;
	};
}