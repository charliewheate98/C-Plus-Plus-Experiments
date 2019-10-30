#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <mutex>

/*
	If we was to run this application currently without a mutex. The threads would be both trying to access the john and phil age variables at the same time and would result in a race condition issue
	as there is not mutex protection.

	However, if we was to use mutext to lock and unlock the individual threads, so the threads will be called in a more sensible order and not continously set the age variables in a deterministic fashion.

	Basically, lets say we have a 3D Model, we want to scale it then rotate it.  But we get a issue of race condition. As the two threads will simultaneously be using the 3D Model and scale and rotating. 
	Therefore, we can use mutex to lock it before the scaleing and rotation happens within the threads, so it will not use this 3d model resource simultaneously in both threads and in more of a orderly fashion.
*/
std::mutex myMutex;

// ages for john and phil
float johnAge;
float PhilAge;

/*
	Multi-maps unlike standard maps allow for use of multiple of the same keys and also sort the elements for you! (based on the keys)
*/
void Multimaps()
{
	// lock it using a mutex, so there is not race/deterministic issues with the age variables
	std::lock_guard<std::mutex> quard(myMutex);

	// Multi_map
	std::multimap<std::string, float> _player_m;
	std::multimap<std::string, float>::iterator it2;

	johnAge = 1.0f;
	PhilAge = 4.0f;

	_player_m.insert(std::make_pair("John", johnAge));
	_player_m.insert(std::make_pair("Phil", 4.0f));
	_player_m.insert(std::make_pair("John", johnAge));

	std::cout << "----- Multi Map -------" << std::endl;

	for (it2 = _player_m.begin(); it2 != _player_m.end(); ++it2)
		std::cout << "NPC Name: " << it2->second << std::endl;

	std::cout << "---------------------------" << std::endl;
}

/*
	Multi-maps unlike standard maps allow for use of multiple of the same keys and also sort the elements for you! (based on the keys)
*/
void Standardmaps()
{
	// lock it using a mutex, so there is not race/deterministic issues with the age variables
	std::lock_guard<std::mutex> quard(myMutex);

	// Multi_map
	std::map<std::string, float> _player;
	std::map<std::string, float>::iterator it;

	johnAge = 1.0f;
	PhilAge = 0.5f;

	_player["John"] = johnAge;
	_player["Phil"] = PhilAge;
	_player["John"] = johnAge;

	std::cout << "----- Standard Map -------" << std::endl;

	for (it = _player.begin(); it != _player.end(); ++it)
		std::cout << "NPC Name: " << it->second << std::endl;

	std::cout << "---------------------------" << std::endl;
}


int main(int argc, char** argv)
{
	std::thread thread_01(Multimaps);
	std::thread thread_02(Standardmaps);

	thread_01.join();
	thread_02.join();

	system("pause");
}