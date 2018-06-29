#ifndef OMGLBiomes_H
#define OMGLBiomes_H

#include "Biome.h"
#include "Material.h"
#include "OMGLNoiseGen.h"

class OMGLMountains : public Biome{

  public:
    OMGLMountains() : Biome(new OMGLNoiseBiome1(),new Material(), 1000,-1000) {}

};

class OMGLDesert : public Biome{

  public:
    OMGLDesert() : Biome(new OMGLNoiseBiome3(),new Material(), 500, -500) {}

};
class OMGLBlocky : public Biome{

  public:
    OMGLBlocky() : Biome(new OMGLNoiseBiome2(),new Material(), 200, 0) {}

};
class OMGLPeanuts : public Biome{

  public:
    OMGLPeanuts() : Biome(new OMGLNoiseBiome4(),new Material(), 200, 0) {}

};
#endif
