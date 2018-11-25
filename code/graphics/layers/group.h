/*******************************************************************
   $File:    group.h
   $Date:    Sun, 25 Nov 2018: 20:34
   $Version: 
   $Author:  klek 
   $Notes:   
********************************************************************/

#if !defined(GROUP_H)
#define GROUP_H

#include "../renderable2d.h"

class Group : public Renderable2D
{
private:
    std::vector<Renderable2D*> m_Children;
    mat4 m_TransformationMatrix;

public:
    Group(const mat4& transform);
    void add(Renderable2D* renderable);
    void submit(Renderer2D* renderer) const override;
};

#endif
