#include "hzpch.h"
#include "RenderCommandQueue.h"

#include "Core.h"

void gl_func(int value) { std::cout << "gl_func INT : " << value << std::endl; }
void gl_funcS(std::string value) { std::cout << "gl_func: " << value << std::endl; }

int main()
{
	Hazel::RenderCommandQueue cmd_queue;
	
	{
		int i_data = 12345;
		std::string my_S1 = "STRINGA 1";
		std::string my_S2 = "STRINGA 2";
		std::string my_S3 = "STRINGA 3";
		std::string my_S4 = "STRINGA 4";
		std::string my_S5 = "STRINGA 3";
		std::string my_S6 = "STRINGA 4";
		std::string my_S7 = "STRINGA 7";

		// Testing int value
		RENDER({ gl_func(i_data); }, i_data);

		// Testing int strings
		RENDER({ gl_funcS(my_S3); }, my_S2, my_S1, my_S4, my_S3);
		RENDER({ gl_funcS(my_S2); }, my_S1, my_S2, my_S3);
		RENDER({ gl_funcS(my_S1); }, my_S2, my_S3, my_S4, my_S5, my_S6, my_S1);
		RENDER({ gl_funcS(my_S1); gl_funcS("Funzione Scipt"); }, my_S2, my_S3, my_S4, my_S5, my_S6, my_S1);

		// simulate this/self
		RENDER_S({ gl_func(self); });
		RENDER_S({ gl_funcS("STRINGA TEXT"); });
	}
	cmd_queue.Execute();

	std::cin.get();
}
