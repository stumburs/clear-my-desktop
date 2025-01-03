#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <ctime>

std::size_t NumberOfFilesInDirectory(std::filesystem::path path)
{
    return std::distance(std::filesystem::directory_iterator(path), std::filesystem::directory_iterator{});
}

std::string GetCurrentDate()
{

    std::time_t current_time = std::time(nullptr);
    struct tm local_time;
    localtime_s(&local_time, &current_time); // Get local time

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << 1900 + local_time.tm_year << '-' << 1 + local_time.tm_mon << '-' << local_time.tm_mday;

    return ss.str();
}

void MoveFiles(std::filesystem::path src, std::filesystem::path dst)
{
    for (const auto &entry : std::filesystem::directory_iterator(src))
    {
        try
        {
            // Skip desktop.ini
            if (entry.path().filename() == "desktop.ini")
                continue;
            std::filesystem::path new_file_path = dst / entry.path().filename();
            std::filesystem::rename(entry.path(), new_file_path);
            std::cout << "Successfully moved: " << entry.path().filename() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
}

int main(int argc, char *argv[])
{
    std::string username = getenv("USERNAME");
    std::filesystem::path desktop_path = std::filesystem::path("C:\\Users\\" + username + "\\Desktop");

    // -1 because ignoring desktop.ini
    std::cout << "Files found on Desktop: " << NumberOfFilesInDirectory(desktop_path) - 1 << std::endl;

    std::filesystem::path target_path = std::filesystem::path("C:\\Users\\" + username + "\\Documents");

    std::filesystem::create_directory(target_path / GetCurrentDate());
    target_path /= GetCurrentDate();
    MoveFiles(desktop_path, target_path);

    return 0;
}