#include "read_tarfile.h"

// https://github.com/libarchive/libarchive/wiki/Examples

void readTarFile() {
	struct archive *oldArchive = archive_read_new();
	struct archive *newArchive = archive_write_disk_new();
	struct archive_entry *entry;	

	archive_read_support_filter_all(oldArchive);  // enable all decompression filter
	archive_read_support_format_all(oldArchive);  // enable support for all formats
   
    std::string fileName = "flash_player_ppapi_linux.x86_64.tar.gz";
    
    // int archive_read_open_filename(struct archive *, const char *filename, 
    //                                size_t block_size); 
    // returns ARCHIVE_OK on success	
	if (archive_read_open_filename(oldArchive, fileName.c_str(), 10240) != ARCHIVE_OK)
        return;
    
    // convert user names to ids
	archive_write_disk_set_standard_lookup(newArchive);
	
    // archive_read_next_header()
    // Read the header for the next entry and return a pointer to a
    // struct archive_entry
	while (archive_read_next_header(oldArchive, &entry) == ARCHIVE_OK) {
	  const std::string fileToExtract = archive_entry_pathname(entry);
      std::string placeToExtract;
      
      std::cout << "entry ... " << entry << "\n";

	  if(fileToExtract == "manifest.json" || fileToExtract == "libpepflashplayer.so") {        
        placeToExtract = "/usr/lib/chromium-browser/plugins/" + fileToExtract;
        archive_entry_set_pathname(entry, placeToExtract.c_str());  // update the location to extract
        
        std::cout << "Extracting ..." << fileToExtract << "\n";
	  	archive_write_header(newArchive, entry);  // write a header based on archive_entry
	  	copy_data(oldArchive, newArchive);  // pull data from read archive and write to write archive
	  }
	  archive_read_data_skip(oldArchive);  // returns next available data block for entry
	}
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
      return (r);
    }

    r = archive_write_data_block(aw, buff, size, offset);
    if (r < ARCHIVE_OK) {
      std::cout << archive_error_string(aw) << "\n";
      return (r);
    }
  }
}

