#include "pitch.hh"
#include "ffmpeg.hh"
#include <boost/math/special_functions/fpclassify.hpp>

int main(int argc, char **argv) {
	// Load audio
	FFmpeg mpeg(false, true, argv[1], 48000);
	int64_t position = 0;

	da::sample_t *sample = new da::sample_t(1500);
	da::pcm_data data(sample, 1500, 2, 48000);

	// wait for ffmpeg to be ready
	// TODO: fix this it is probably not enough
	while( boost::math::isinf(mpeg.duration()) );

	while( mpeg.audioQueue(data, position) ) {
		std::cout << "Position: " << position << " " << double(position) / double(48000*2)<< std::endl;
	}

	std::cout << "Duration: " << mpeg.duration() << std::endl;
	return EXIT_SUCCESS;
}