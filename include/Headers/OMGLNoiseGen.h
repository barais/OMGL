#ifndef OMGLNoiseGen_H
#define OMGLNoiseGen_H

#include <vector>

#include "FastNoise.h"
#include "NoiseGen.h"

class OMGLNoiseGen : public virtual NoiseGen {
  protected:
    std::vector<std::vector<FastNoise*>> m_Noises;
  
  public:
    OMGLNoiseGen(unsigned int nbNoises = DEFAULT_NB_NOISES);
        

};

class OMGLNoiseCloud : public virtual OMGLNoiseGen{
  protected:
    FastNoise* m_Mix;
    float compute(float x, float y) { return compute2(x,y)[0]; }
    float* compute2(float x, float y);

  public:
    OMGLNoiseCloud() : OMGLNoiseGen(1) {}

};

typedef OMGLNoiseCloud OMGLNoiseCloudVerso;

class OMGLNoiseCloudRecto : public OMGLNoiseCloud{
  public:
    float compute(float x, float y);
};

class OMGLNoiseBiome : public virtual OMGLNoiseGen{
  protected:
    virtual float compute(float x, float y){return 0.0f;}
    float compute1(float x, float y);
    float compute4(float x, float y);

  public:
    OMGLNoiseBiome() : OMGLNoiseGen(3) {}

};

class OMGLNoiseBiome1 : public OMGLNoiseBiome{
  public:
    float compute(float x, float y);
};

class OMGLNoiseBiome2 : public OMGLNoiseBiome{
  public:
    float compute(float x, float y);
};

class OMGLNoiseBiome3 : public OMGLNoiseBiome{
  public:
    float compute(float x, float y);
};

class OMGLNoiseBiome4 : public OMGLNoiseBiome{
  public:
    float compute(float x, float y);
};

class OMGLNoiseBiome5 : public OMGLNoiseBiome{
  public:
    float compute(float x, float y);
};

class OMGLNoiseBiome6 : public OMGLNoiseBiome{
  public:
    float compute(float x, float y);
};

class OMGLNoiseBiome7 : public OMGLNoiseBiome{
  public:
    float compute(float x, float y);
};

#endif 