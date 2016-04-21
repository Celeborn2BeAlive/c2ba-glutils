#include <iostream>

#include <glutils/info.hpp>
#include <glutils/opengl.hpp>

namespace c2ba
{
namespace glutils
{

int main(int argc, char* argv[])
{
    std::cout << "TODO: run tests for " << LIBRARY_NAME << " version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

    // Should fail: (no window opened)
    std::cout << int(initOpenGL()) << std::endl;

    return 0;
}

}
}

int main(int argc, char* argv[])
{
    return c2ba::glutils::main(argc, argv);
}