#ifndef HPBAR_H
#define HPBAR_H

#include "QQuickView"
class Hpbar
{
public:
    Hpbar();
    int show();
    float saohpbarX       = 0;
    float saohpbarY       = 0;
    void setXY(float saohpbarX,float saohpbarY);
    QQuickView sao_hpbar;
};

#endif // HPBAR_H
