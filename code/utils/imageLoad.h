/*******************************************************************
   $File:    imageLoad.h
   $Date:    Mon, 03 Dec 2018: 16:35
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(IMAGELOAD_H)
#define IMAGELOAD_H

#include <string>
#include <FreeImage.h>

static BYTE *load_image(const char* fileName, GLsizei *width, GLsizei *height)
{
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP *dib = nullptr;
    fif = FreeImage_GetFileType(fileName, 0);
    if ( fif == FIF_UNKNOWN )
    {
        fif = FreeImage_GetFIFFromFilename(fileName);
    }
    if ( fif == FIF_UNKNOWN )
    {
        return nullptr;
    }

    if ( FreeImage_FIFSupportsReading(fif) )
    {
        dib = FreeImage_Load(fif, fileName);
    }

    if ( !dib )
    {
        return nullptr;
    }

    BYTE *result = FreeImage_GetBits(dib);
    *width = FreeImage_GetWidth(dib);
    *height = FreeImage_GetHeight(dib);

    return result;    
}

#endif
