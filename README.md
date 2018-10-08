# CIFAR10 Loader written in C++

## Requirement

- C++11

## Use

```cpp
const auto cifar_10_sample = mtk::load_cifar_10("cifar-10-batches-bin/data_batch_1.bin");
for(const auto& sample : cifar_10_sample){
	// type : std::vector<unsigned int>(32 x 32)
	// unsigned int <- 0xrrggbb
	const auto image = std::get<0>(sample);

	// type : int
	const auto label = std::get<1>(sample);
}
```
