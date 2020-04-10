//
// Created by jake on 09/04/2020.
//

#include "Window.h"
#include <cassert>
using namespace Panic;

Window::Window(std::string title) {
	assert(("Please call Panic::init() before using other library functions!", SDL_WasInit(SDL_INIT_VIDEO) != 0));

	// Try to create a SDL window
	window = SDL_CreateWindow(title.c_str(), 100, 100, 200, 200, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::cerr << "Failed to create window "<< title <<"!\nError: " << SDL_GetError() << std::endl;
		abort();
	}

	// Now that we definitely have a window, we can create a renderer for that window
	renderer = SDL_CreateRenderer(window, -1, 0); // SDL will prioritise hardware accellerated drivers
	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer for window " << title << "!\nError: " << SDL_GetError << std::endl;
	}

	consoles = std::vector<Console*>();
	consoles.resize(255);
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Window::render() {
	SDL_RenderClear(renderer);
	for (Console *x : consoles) {
		if (x) {
			x -> render(renderer);
		}
	}
	SDL_RenderPresent(renderer);
}

Console *Window::createConsole(int x, int y, int w, int h, byte index) {
	consoles[index] = new Console(x, y, w, h, renderer);

	return consoles[index];
}

Console *Window::getConsole(byte index) {
	return consoles[index];
}

void Window::removeConsole(byte index) {
	consoles[index] = nullptr;
}