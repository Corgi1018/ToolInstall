#include <iostream>
#include <filesystem>

 
/**
 * 类不要在根名称空间下
 * 函数命名要求
 * 形参命名要求（in，out）
 * 
*/
class folder {
public:
void Createdir(std::filesystem::path Path);
void Copyfile(const std::filesystem::path& from,const std::filesystem::path& to);
void folder_exists(const std::filesystem::path&p, std::filesystem::file_status s=std::filesystem::file_status{});
std::filesystem::path getDocumentPath();
private:
};
