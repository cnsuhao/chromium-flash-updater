# chromium-flash-updater
Update flash player for chromium browser (Ubuntu 16.04 x64)    
  
 * This is a program to install flash player ppapi (Chromium Only) for Ubuntu 16.04
 * You need to download flash_player_ppapi_linux.x86_64.tar.gz from Adobe website
 * put the tar.gz file and the program in the same folder. 
 * Note: 
    + This program might not work in other distros since different distros store the flash player in different locations
    + Flash is dying and being replaced by Html5. This is just a temporary small project for Flash games and learning purpose 
 * Usage:  
    + `sudo ./flash-upgrade`
 * OR
    + `sudo ./flash-upgrade filename.tar.gz`

 * Special thanks to 
    + libarchive - http://libarchive.org
    + JSON for modern c++ - https:://github.com/nlohmann/json 
    + My teachers for teaching me how to use linux libraries, json, etc. 
 
 * Build instructions:
    + sudo apt install libarchive-dev 
    + download the "json.hpp" https://github.com/nlohmann/json