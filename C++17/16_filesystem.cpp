#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <ctime>

namespace fs = std::filesystem;

void print_last_write_time(const fs::path& path) {
    auto ftime = fs::last_write_time(path);
    auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
    );
    std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
    std::cout << "\t" << "Last write time: " << std::put_time(std::localtime(&cftime), "%F %T") << std::endl;
}

void traverse_directory(const fs::path& path) {
    for (const auto& entry : fs::directory_iterator(path)) 
    {
        std::cout << "Path: " << entry.path() << std::endl;

        if (fs::is_regular_file(entry.path()))
        {
            std::cout << "\t" << "Type:" << "is file." << std::endl;
            std::cout << "\t" << "File Size:" << fs::file_size(entry.path()) << " bytes" << std::endl;
            print_last_write_time(entry.path());
        }
        else if (fs::is_directory(entry.path()))
        {
            std::cout << "\t" << "Type:" << "is directory." << std::endl;
            traverse_directory(entry.path());
        }
        else if (fs::is_symlink(entry.path()))
        {
            std::cout << "\t" << "Type:" << "is symlink." << std::endl;
        }
        else if (fs::is_other(entry.path()))
        {
            std::cout << "\t" << "Type:" << "is other." << std::endl;

        }
        else
        {
            std::cout << "\t" << "Type:" << "Unknown." << std::endl;
        }
    }
}

int main() {
    const std::string path = "C:\\liu\\tmp";
    traverse_directory(path);
    return 0;
}