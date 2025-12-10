#include <fstream>
#include <iostream>

struct highscore
{
	char name[4];
	uint32_t score;
};

int main()
{
	// Write ASCII files.
	{
		std::ofstream highscores("highscores.txt");

		if (!highscores)
		{
			std::cerr << "ERROR: Could not open file for writing." << std::endl;

			return 1;
		}

		highscores << "DAN " << 2014 << std::endl;
		highscores << "TOM " << 2012 << std::endl;
		highscores << "LUC " << 2009 << std::endl;
		highscores << "SUZ " << 1978 << std::endl;

		if (highscores.bad())
		{
			std::cerr << "ERROR: An error occured while writing to the file." << std::endl;

			return 1;
		}

		highscores.close();
		// File will actually close when it goes out of scope.
	}
	
	{
		std::ofstream highscores("highscores.txt", std::ios::app);

		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;

			return 1;
		}

		highscores << "AYM " << 1989 << std::endl;

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to write to file." << std::endl;

			return 1;
		}

		highscores.close();
	}

	{
		std::ifstream highscores("highscores.txt");

		if (!highscores)
		{
			std::cerr << "ERROR: Could not open file for reading." << std::endl;

			return 1;
		}

		char name[4] = {};
		int score = 0;

		while (highscores >> name >> score)
		{
			std::cout << name << " " << score << std::endl;
		}

		if (highscores.bad())
		{
			std::cerr << "ERROR: Could not read from file." << std::endl;

			return 1;
		}

		highscores.close();
		// File will actually close when going out of scope.
	}

	// Writing a binary file.
	{
		std::ofstream highscores("highscores.bin", std::ios::binary);

		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;

			return 1;
		}

		highscore scores[] = {
			{ "DAN", 2014 },
			{ "TOM", 2012 },
			{ "LUC", 2009 },
			{ "SUZ", 1978 },
			{ "AYM", 1989 }
		};

		auto numScores = std::size(scores);

		highscores.write(reinterpret_cast<const char*>(&numScores), sizeof(numScores));
		highscores.write(reinterpret_cast<const char*>(scores), numScores * sizeof(highscore));

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to write to file." << std::endl;

			return 1;
		}

		highscores.close();
	}

	std::cout << std::endl;

	// Reading from a binary file.
	{
		std::ifstream highscores("highscores.bin", std::ios::binary);

		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;

			return 1;
		}

		size_t numEntries = 0;
		highscores.read(reinterpret_cast<char*>(&numEntries), sizeof(numEntries));

		highscore* scores = new highscore[numEntries];

		highscores.read(reinterpret_cast<char*>(scores), numEntries * sizeof(highscore));

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to read from file." << std::endl;

			return 1;
		}

		for (int i = 0; i < numEntries; ++i)
		{
			std::cout << scores[i].name << " " << scores[i].score << std::endl;
		}

		delete[] scores;
		highscores.close(); // Return any system resources ! ...
		// ... Though it will actually close when going out of scope.
	}

	return 0;
}