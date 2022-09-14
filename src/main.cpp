#include <EkHelpers.hpp>

int main()
{
    InitHelpers::InitGlfw();
    InitHelpers::CreateInstance();
    InitHelpers::PickPhysDev();
    std::cout << "Finished" << std::endl;
    return 0;
}
