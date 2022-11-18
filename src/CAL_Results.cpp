#include "CAL_Results.h"

void RESULTS::sorting()
{
	// create a empty vector of pairs
    std::vector<std::pair<std::string, unsigned int>> vec;

	// copy key-value pairs from the map to the vector
    std::map<std::string, unsigned int> :: iterator it2;
    for (it2 = PlayerInfo.begin(); it2 != PlayerInfo.end(); it2++) 
    {
        vec.push_back(std::make_pair(it2->first, it2->second));
    }

    std::sort(vec.begin(), vec.end(), [](auto p1, auto p2){return p1.second > p2.second;}); 

	// print the vector
	std::cout << "The map, sorted by value is: " << std::endl;
	for (int i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i].first << ": " << vec[i].second << std::endl;
	}
}