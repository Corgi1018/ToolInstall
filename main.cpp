#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "src/file.h"
int main(int, char **)
{
    folder f;
    const std::filesystem::path fromPath{"//192.168.10.240/public/mygwaibao2/Tool/share"};
    const std::filesystem::path toPath=f.getDocumentPath();
    std::cout<<"path:"<<toPath<<'\n';
    f.Createdir(toPath);
    const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;
    try
    {
        std::filesystem::copy(fromPath, toPath, copyOptions);
    }
    catch (std::filesystem::filesystem_error const &ex)
    {
        std::cout << "what():" << ex.what() << '\n';
    }

}

