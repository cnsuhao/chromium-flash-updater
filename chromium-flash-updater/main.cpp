/**
 * Author: Nyan Tun
 * email: ntun4gaming[at]gmail[dot]com
 *
 * This is a program to install flash player ppapi (Chromium Only) for Ubuntu 16.04
 * You need to download flash_player_ppapi_linux.x86_64.tar.gz from Adobe website
 * put the tar.gz file and the program in the same folder. 
 *
 * Note: 
 * 1. This program might not work in other distros since different distros store
 * the flash player in different locations
 * 2. Flash is dying and being replaced by Html5. This is just a temporary small project 
 * for Flash games and learning purpose
 * 
 * Usage:  
 * 	sudo ./flash-upgrade
 * OR
 * 	sudo ./flash-upgrade filename.tar.gz

 * Special thanks to 
 * 1. libarchive - http://libarchive.org 
 * 2. JSON for modern c++ https:://github.com/nlohmann/json 
 * 3. My teachers for teaching me how to use linux libraries, json, etc. 
 * 
 * Build instructions:
 * 1. sudo apt install libarchive-dev 
 * 2. download the "json.hpp" https://github.com/nlohmann/json
 * 
 * Challenges: 
 * 1. Dealing with tar file is quite difficult. First, I tried libtar, but lack of documentation
 *    prevents me from using it. Found a few methods to use such as Boost and system call, but 
 *    decided to use libarchive instead. 
 * 2. Learned how to use include files. First query the files with dpkg-query -L 
 *  	dpkg-query -L libarchive-dev | grep "include" // include files for header
 *	dpkg-query -L libarchive-dev | grep "lib"  // use with gcc - use -l instead of -lib
 * 	e.g., gcc -larchive ... 
 */

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include "json.hpp"
#include "read_tarfile.h"


int main(int argc, char *argv[]) {
    using json = nlohmann::json;
    std::string fileName;
    
    if(argc < 2) {
        std::cout << "\nUsage: sudo ./flash-upgrade filename.tar.gz\n";
        std::cout << "File name is not given. Using flash_player_ppapi_linux.x86_64.tar.gz instead\n\n";
        fileName = "flash_player_ppapi_linux.x86_64.tar.gz";  
    } else {
        fileName = argv[1];
    }        
    
    try {
        // extract manifest.json and libpepflashplayer.so to 
        // /usr/lib/chromium-browswer/plugins/
        extractTarFile(fileName);    
    
        // read the recently extracted manifest.json file using nlohmann
        std::ifstream inputFile("/usr/lib/chromium-browser/plugins/manifest.json");
        if (inputFile) {
            json myJson;
            inputFile >> myJson;
            inputFile.close();  
            
            // parse Chromium version from json
            std::string chromeVersion = myJson["version"];
            chromeVersion = "CHROMIUM_FLAGS=\""  
                            "--ppapi-flash-path=/usr/lib/chromium-browser/plugins/libpepflashplayer.so " 
                            "--ppapi-flash-version=" + chromeVersion + "\"";    

            // C++ experimental features - filesystem
            // required since ofstream can't create directory
            // need -lstdc++fs with gcc
            // Check for empty directory and create one if the folder is empty
            // 
            namespace fs = std::experimental::filesystem;
            if(! fs::exists("/etc/chromium-browser")) {
                fs::create_directory("/etc/chromium-browser");
            }

            std::ofstream outputFile("/etc/chromium-browser/default");
            if(outputFile) {
                outputFile << chromeVersion << "\n";
            } else {
                std::cerr << "cannot open file...\n";
            }
            outputFile.close();

        } else {
            std::cerr << "cannot open file... \n";
        }
        
    
    } catch (const char *s){
        std::cout << s << "\n"; 
    }
    
	return 0;
}
