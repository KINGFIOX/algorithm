#include <cstdio>
#include <filesystem>
#include <iostream>
#include <stack>

namespace fs = std::filesystem;

#if 0

class Solution {
public:
    static unsigned int countFilesInDirectory(const fs::path& path)
    {
        unsigned int fileCount = 0;

        // 检查给定的路径是否存在以及是否为目录
        if (fs::exists(path) && fs::is_directory(path)) {
            // 遍历给定目录及其所有子目录
            for (const auto& entry : fs::recursive_directory_iterator(path)) {
                // 如果当前条目是文件，则增加计数器
                if (fs::is_regular_file(entry)) {
                    ++fileCount;
                }
            }
        }

        return fileCount;
    }
};

#else

class Solution {
public:
    static int getFileNumber(const fs::path& folderPath)
    {
        // 检查路径是否存在以及它是目录还是文件
        if (!fs::exists(folderPath)) {
            return 0;
        }
        if (fs::is_regular_file(folderPath)) {
            return 1; // 如果是文件，直接返回1
        }

        std::stack<fs::path> stack;
        stack.push(folderPath);
        int files = 0;

        while (!stack.empty()) {
            fs::path folder = stack.top();
            stack.pop();

            // 使用异常处理来避免无权限访问时的程序崩溃
            try {
                for (const auto& entry : fs::directory_iterator(folder)) {
                    if (fs::is_regular_file(entry.status())) {
                        files++; // 是文件，则增加文件计数
                    } else if (fs::is_directory(entry.status())) {
                        stack.push(entry.path()); // 是目录，则将目录路径加入栈中
                    }
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error accessing " << folder << ": " << e.what() << '\n';
            }
        }
        return files;
    }
};

#endif

int main(void)
{
    int files = Solution::getFileNumber(".");
    std::cout << files << std::endl;
}