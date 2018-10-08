#ifndef __CIFAR10_HPP__
#define __CIFAR10_HPP__

#include <fstream>
#include <vector>
#include <tuple>
#include <stdexcept>

namespace{
namespace mtk{
constexpr std::size_t CIFAR_10_DIM = 32;
using label_t = int;
using image_t = std::vector<unsigned int>;
using sample_t = std::tuple<image_t, label_t>;
std::vector<sample_t> load_cifar_10(const std::string& filename) {
	std::ifstream ifs(filename);
	if(!ifs){
		throw std::runtime_error("No such file : " + filename);
	}

	// compute file size
	ifs.seekg(0, std::fstream::end);
	const auto end_pos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::fstream::beg);
	const auto begin_pos = ifs.tellg();

	// validate size
	if((end_pos - begin_pos) % (1 + CIFAR_10_DIM * CIFAR_10_DIM * 3) != 0){
		throw std::runtime_error("Invalid data size");
	}
	const std::size_t sample_size = (end_pos - begin_pos) / (1 + CIFAR_10_DIM * CIFAR_10_DIM * 3);

	// load sample data
	std::vector<sample_t> samples;
	for(auto i = decltype(sample_size)(0); i < sample_size; i++){
		label_t label;
		image_t image(CIFAR_10_DIM * CIFAR_10_DIM);

		// load label
		ifs.read((char*)&label, 1);

		// load image data
		for(int c = 2; c >= 0; c--){
			for(auto y = decltype(CIFAR_10_DIM)(0); y < CIFAR_10_DIM; y++){
				for(auto x = decltype(CIFAR_10_DIM)(0); x < CIFAR_10_DIM; x++){
					unsigned int byte;
					ifs.read((char*)&byte, 1);
					image[x + y * CIFAR_10_DIM] |= (byte << (8 * c));
				}
			}
		}
		samples.push_back(std::make_tuple(image, label));
	}
	return samples;
}
}
}

#endif
