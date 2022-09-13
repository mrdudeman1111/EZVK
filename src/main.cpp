#include <EkHelpers.hpp>

int main()
{
    InitHelpers::InitGlfw();
    InitHelpers::CreateInstance();
    
    std::cout << "Finished" << std::endl;
    return 0;
}
