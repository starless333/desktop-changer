#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <random>
#include<regex>
using namespace std;

size_t ptr = 0;
int line_num;
string contents;
string file_name;
string wallpaper_dir;
string template_sway = "exec = swaybg -m fill -i ";
using namespace std;

vector<string> images;
#define BG "swaybg"
void error(int argc) {
  if(argc > 3 || argc == 0) {
    cerr << "Please first provide your hyprland.conf and a folder to your wallpapers.\n"; 
    exit(EXIT_FAILURE);
  }
}

void find_line(char** argv) {
  line_num = 0;
  file_name = argv[1];
  ifstream file(file_name);
  if(!file) {
    throw("Could Not Open Configuration File\n");
  }
  string temp;
  while(file) {
    getline(file,temp);
    if(temp.find("swaybg") != string::npos && temp[0] != '#') {
      contents = temp;
      break;
    }
    line_num++;
  }
  // we 0 index line_num because we are eventually gonna have to put it in a vector<>();
  file.close();
}

// This will get all of the wallpapers given some path
void get_wallpapers() {
  namespace fs = std::filesystem;
  try {
    // Iterate through each file in the directory
    for (const auto &entry : fs::directory_iterator(wallpaper_dir)) {
      // Check if it's a regular file
      if (entry.is_regular_file()) {
        images.push_back(entry.path());
      }
    }
    // NOTE: making the wallpapers random is more fun!
    std::shuffle(std::begin(images), std::end(images), std::default_random_engine { std::random_device{}() });
  } catch (const fs::filesystem_error &ex) {
    std::cerr << "Error accessing directory: \n" << ex.what() << '\n';
  }
}

void read_and_write(const string& wallpaper) {
  ifstream file(file_name);
  if(!file) {
    cerr << "Could not open config file\n";
    exit(EXIT_FAILURE);
  }
  vector<string> lines;
  string temp;
  // template_sway is something that we are going to push_back();
  while(file) {
    getline(file,temp);
    lines.push_back(temp);
  }
  file.close();
  lines[line_num] = template_sway + wallpaper;
  ofstream write_file(file_name);
  cout << line_num << " " << lines[line_num] << '\n';
  for(size_t i = 0; i < lines.size(); i++) {
    if(i != lines.size()-1)write_file << lines[i] << '\n';
    else write_file << lines[i];
  }
  write_file.flush();
  write_file.close();
}

void exec() {
  while(1) {
    auto curr_time = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(curr_time);
    std::tm* now_tm = std::localtime(&now_c);
    int seconds_until_next_hour = (60 - now_tm->tm_min) * 60 - now_tm->tm_sec;
    // uncomment this in a little lol.
    std::this_thread::sleep_for(std::chrono::seconds(seconds_until_next_hour));
    // Do stuff.
    if(ptr >= images.size()) {
      ptr = 0;
    }
    string wallpaper = images[ptr++];
    read_and_write(wallpaper);
 }
}
    
int main(int argc, char** argv) {
  error(argc);
  find_line(argv);
  wallpaper_dir = argv[2];
  get_wallpapers();
  exec();
  return 0;
}

