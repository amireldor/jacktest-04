#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

#include "jackengine.h"

int main(int argc, char *argv[])
{
	cout << "Hello." << endl;

	// start engine
	AudioEngine *audio_engine = new JackEngine();

	// load and mix sounds
/*	AudioBuffer *sound1 = new AudioBuffer("sound1.wav");
	delete sound1;*/

	cout << "Hit RETURN To quit" << endl;
	cin.ignore();

	// shutdown
	delete audio_engine;

	return EXIT_SUCCESS;
}
