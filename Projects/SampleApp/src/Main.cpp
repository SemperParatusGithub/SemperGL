#include <SemperGL/SemperGL.h>


int main()
{
	SemperGL::Core::Init();
	SemperGL::Window window("Snake", 1280, 720);

	while (window.IsOpen())
	{
		window.OnUpdate();
		window.Clear();
	}
}