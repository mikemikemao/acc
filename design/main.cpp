#include <iostream>

int main() {
#ifdef ENABLE_FACTORY_METHOD
    std::cout << "BinarySplitter" << std::endl;
    BinarySplitterFactory binarySplitterFactory;
    FactoryMethod factoryMethod(binarySplitterFactory);
    factoryMethod.test();
#endif
    return 0;
}
