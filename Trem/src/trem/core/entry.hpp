#pragma once
#include <trem/core/game.h>

int main(const int argc, const char* args[])
{  
	auto game = Trem::createGame();
	game->start();
	game->run();
	game->shutdown();

	std::cout << "Press Enter to exit...";
	std::cin.get();
}

