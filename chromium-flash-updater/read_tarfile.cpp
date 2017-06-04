#include "read_tarfile.h"

// https://github.com/libarchive/libarchive/wiki/Examples

void extractTarFile(std::string fileName) {
	struct archive *oldArchive = archive_read_new();
	struct archive *newArchive = archive_write_disk_new();
	struct archive_entry *entry = archive_entry_new();
	
	archive_read_support_filter_all(oldArchive);  // enable all decompression filter
	archive_read_support_format_all(oldArchive);  // enable support for all formats    
    
    // int archive_read_open_filename(struct archive *, const char *filename, 
    //                                size_t block_size); 
    // returns a status code (ARCHIVE_OK) on success	
	if (archive_read_open_filename(oldArchive, fileName.c_str(), 10240) != ARCHIVE_OK)
        throw "cannot read the file...";
    
    // convert user names to ids
	archive_write_disk_set_standard_lookup(newArchive);
	
    // archive_read_next_header()
    // Read the header for the next entry and return a pointer to a
    // struct archive_entry
	while (archive_read_next_header(oldArchive, &entry) == ARCHIVE_OK) {
	  const std::string fileToExtract = archive_entry_pathname(entry);
      std::string pathName; 

      // extract manifest.json to /usr/lib/chromium-browser/plugins
      // extract libpepflashplayer.so to /usr/lib/chromium-browser/plugins
	  if(fileToExtract == "manifest.json" || fileToExtract == "libpepflashplayer.so") {        
        pathName = "/usr/lib/chromium-browser/plugins/" + fileToExtract;
        archive_entry_set_pathname(entry, pathName.c_str());  // update the location to extract        
        
	  	archive_write_header(newArchive, entry);  // write a header based on archive_entry
	  	copy_data(oldArchive, newArchive);  // pull data from read archive and write to write archive
        std::cout << "Extracting... " << fileToExtract << "\n";
	  }
	  archive_read_data_skip(oldArchive);  // returns next available data block for entry
	}
    
    // clear memory
	archive_write_finish_entry(newArchive);
	archive_read_close(oldArchive);
	archive_read_free(oldArchive);
	archive_write_close(newArchive);
	archive_write_free(newArchive);    
}

// pull data from read archive and write to write archive
static int copy_data(struct archive *ar, struct archive *aw) {
  int r = -1;
  const void *buff;
  size_t size;
  long int offset;

  for (;;) {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    if (r == ARCHIVE_EOF) {
      return (ARCHIVE_OK);
    }
    if (r < ARCHIVE_OK) {
      throw "cannot read the file...";
    }

    r = archive_write_data_block(aw, buff, size, offset);
    if (r < ARCHIVE_OK) {  
      std::cerr << archive_error_string(aw) << "\n"; 
      throw "please run the program with sudo\n";
           
    }
  }
}


