#ifndef __DATAMANAGER_H
#define __DATAMANAGER_H

#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

class DataManager {
	public:
		static void saveHighScore(int highScore);
		static int loadHighScore();
};
#endif
