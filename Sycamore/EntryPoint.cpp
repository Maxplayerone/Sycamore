#include"Sycamore.h"

#ifdef SM_WINDOWS
	int main(int argc, char** argv) {
		std::unique_ptr<Window> window(new Window);
		window->Run();
		return 0;
	}
#endif