#include "MagicTown.h"

int main()
{
	MagicTown* magic_town;
	magic_town = new MagicTown();
	magic_town->PlayGame();
	system("pause");
	delete magic_town;
}