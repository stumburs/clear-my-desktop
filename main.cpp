#include <iostream>
#include <cassert>
#include <filesystem>
#include <Windows.h>
#include <ctime>

std::size_t NumberOfFilesInDirectory(std::filesystem::path path)
{
    using std::filesystem::directory_iterator;
    return std::distance(directory_iterator(path), directory_iterator{});
}

std::string GetCurrentDate()
{
    const char *months[] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    std::time_t current_time = std::time(nullptr);
    struct tm local_time;
    localtime_s(&local_time, &current_time); // Get local time

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << local_time.tm_mday << " "
       << months[local_time.tm_mon] << " "
       << 1900 + local_time.tm_year;

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
            std::cout << "Moved: " << entry.path() << " to " << new_file_path << std::endl;
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
    std::cout << "Files found in " << desktop_path << ": " << NumberOfFilesInDirectory(desktop_path) - 1 << std::endl;

    std::filesystem::path target_path = std::filesystem::path("C:\\Users\\" + username + "\\Documents");

    std::filesystem::create_directory(target_path / GetCurrentDate());
    target_path /= GetCurrentDate();
    MoveFiles(desktop_path, target_path);

    return 0;
}