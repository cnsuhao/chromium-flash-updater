#ifndef READ_TARFILE_H
#define READ_TARFILE_H

#include <iostream>
#include <cstdlib>
#include <archive.h>
#include <archive_entry.h>
static int copy_data(struct archive *ar, struct archive *aw);
void extractTarFile(std::string fileName);

class Error {
    
};

#endif /* READ_TARFILE_H */

