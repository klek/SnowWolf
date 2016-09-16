/*******************************************************************
   $File:    fileutils.cpp
   $Date:    Fri, 16 Sep 2016: 14:58
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#include <iostream>
#include "fileutils.h"

std::string read_file(const char* filepath)
{
    FILE* file = fopen(filepath, "r");

    // Test if the fileopen worked
    if ( file != NULL ) {
        // Search for the end of the file
        fseek(file, 0, SEEK_END);
        // Get how many bytes the file contains
        unsigned long length = ftell(file);
        // Allocate memory for a char array plus 1 extra byte for line ending
        char* data = new char[length + 1];
        // Set all memory to zero to get rid of artifacts in memory
        memset(data, 0, length + 1);
        // Search for the start of the file again
        fseek(file, 0, SEEK_SET);
        // Copy data from our file into the newly created char array
        fread(data, 1, length, file);
        // Close the file
        fclose(file);

        // Convert our char array into a string
        std::string result(data);
        // Delete the allocated memory
        delete[] data;
        // Finally return the string
        return result;
    }
    // TODO(klek): Insert logger here
    std::cout << "Failed to open file, " << filepath << "!" << std::endl;
    return NULL;

}
