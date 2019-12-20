#include "DataManager.h"

void DataManager::saveHighScore(int highScore) {
	#ifdef __linux__
	std::string homedir;

	//getting home directory in linux
	homedir = getenv("HOME");
	if (homedir.empty()) {
		homedir = getpwuid(getuid())->pw_dir;
	}

	int prevHighScore = loadHighScore();

	if(highScore > prevHighScore) {
		std::ofstream outfile;
		outfile.open(homedir + "/defender.pref", std::ofstream::trunc);

		int encryptedScore = highScore ^ 0xface;
		outfile << encryptedScore;
		outfile.close();
	}
	#endif

	#ifdef _WIN32
	wchar_t* path = new wchar_t[512];
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
	if (SUCCEEDED(hr)) {
		wstringstream filepath;
		filepath << localAppData << "\\defender.pref";
		std::string path_string;
		std::filepath.get(path_string,256);

		int prevHighScore = loadHighScore();

		if(highScore > prevHighScore) {
			std::ofstream outfile(path_string);
			int encryptedScore = highScore ^ 0xface;
			outfile << encryptedScore;
			outfile.close();
		}
	}
	CoTaskMemFree(static_cast<void*>(path));
	#endif
}

int DataManager::loadHighScore() {
	#ifdef __linux__
	std::string homedir;

	//getting home directory in linux
	homedir = getenv("HOME");
	if (homedir.empty()) {
		homedir = getpwuid(getuid())->pw_dir;
	}

	//opening pref file
	std::ifstream infile(homedir + "/defender.pref");

	int highScore;
	if( infile.is_open()) {
		int encryptedScore;
		infile >> encryptedScore;
		highScore = encryptedScore ^ 0xface;
		infile.close();
	}
	else {
		highScore = 0;
	}
	return highScore;
	#endif

	#ifdef _WIN32

	wchar_t* path = new wchar_t[512];
	hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
	if (SUCCEEDED(hr)) {
		wstringstream filepath;
		filepath << localAppData << "\\defender.pref";
		std::string path_string;
		std::filepath.get(path_string,256);
		std::ifstream infile(path_string);

		int highScore;
		if(infile.is_open()) {
			int encryptedScore;
			infile >> encryptedScore;
			highScore = encryptedScore ^ 0xface;
			infile.close();
		}
		else {
			highScore = 0;
		}
	}
	CoTaskMemFree(static_cast<void*>(path));

	return highScore;
	#endif
}
