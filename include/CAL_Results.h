#ifndef CAL_RESULTS_H
#define CAL_RESULTS_H

#include<MASTER.h>

class RESULTS{
    public:
        void sorting();
    private:
        std::map<std::string, unsigned int> PlayerInfo  = {
		{"coconut", 99}, {"apple", 1}, {"peach", 30}, {"mango", 0}
	    };
};

#endif