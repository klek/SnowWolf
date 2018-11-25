/*******************************************************************
   $File:    tileLayer.h
   $Date:    Sat, 24 Nov 2018: 13:56
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(TILELAYER_H)
#define TILELAYER_H

#include "layer.h"
#include "../batchrenderer2d.h"

class TileLayer : public Layer
{
protected:

public:
    TileLayer(Shader *shader);
    ~TileLayer();
};


#endif
