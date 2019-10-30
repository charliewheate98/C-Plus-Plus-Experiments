#include <iostream>
#include <string>
#include <map>

/*
	Multi-maps unlike standard maps allow for use of multiple of the same keys and also sort the elements for you! (based on the keys)
*/
void Multimaps()
{
	// Multi_map
	std::multimap<std::string, float> _player_m;
	std::multimap<std::string, float>::iterator it2;

	_player_m.insert(std::make_pair("John", 1.0f));
	_player_m.insert(std::make_pair("Phil", 4.0f));
	_player_m.insert(std::make_pair("John", 2.5f));

	std::cout << "----- Multi Map -------" << std::endl;

	for (it2 = _player_m.begin(); it2 != _player_m.end(); it2++)
		std::cout << "NPC Name: " << it2->second << std::endl;

	std::cout << "---------------------------" << std::endl;
}

int main(int argc, char** argv)
{
	Multimaps();
	
	system("pause");
}
