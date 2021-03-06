#include <ctime>
#include <stdlib.h>

#include "IGWordGenerator.h"
#include "../graphics/perlin/Perlin.h"


IGWordGenerator* IGWordGenerator::instance = IMP_NULL;

//--------------------------------------------------------------
IGWordGenerator::IGWordGenerator()
{
    InitRand();
    IGWordGenerator::instance = this;
}

//--------------------------------------------------------------
IGWordGenerator::~IGWordGenerator()
{
    IGWordGenerator::instance = IMP_NULL;
}

//--------------------------------------------------------------
IGWordGenerator* IGWordGenerator::GetInstance()
{
    if(IGWordGenerator::instance == IMP_NULL)
        new IGWordGenerator();

    return IGWordGenerator::instance;
}

//--------------------------------------------------------------
void IGWordGenerator::Generate(IGWorld* _world)
{
    imp::Int32 height = _world->GetSizeZ();

    Perlin perlin((float)_world->GetSizeX(), (float)_world->GetSizeY(), 0, (float)height);
    perlin.generateSeedMap();
    perlin.smoothSeedMap();
    for(int octave=0; octave<PERLIN_OCTAVE_COUNT; ++octave)
        perlin.generateOctaveMap(octave);

    perlin.compileResult();
    t_perlinMap seed = perlin.getResult();

    for(imp::Uint32 x = 0; x<_world->GetSizeX(); ++x)
    for(imp::Uint32 y = 0; y<_world->GetSizeY(); ++y)
    {
        int value = (int)seed.data[INDEX_XY((int)x,(int)y,(int)seed.width, (int)seed.height)];

        imp::Int32 localElevation = (imp::Int32)value;//Rand(height*3/4,height);

        imp::Int32 z = 0;
        for(; z<localElevation-1; ++z)
            _world->SetValue(x,y,(imp::Uint32)z, 4);

		for(;z<localElevation; ++z)
			_world->SetValue(x,y,(imp::Uint32)z,1);

        for(; z<height; ++z)
            _world->SetValue(x,y,(imp::Uint32)z,0);
    }

    fprintf(stdout, "generate termine\n");
}

//--------------------------------------------------------------
void IGWordGenerator::Generate(IGWorld* _world, const imp::Texture* _heightmap)
{
	    imp::Uint32 height = _world->GetSizeZ();

	    int imgw = _heightmap->getWidth();
	    int imgh = _heightmap->getHeight();

		for(imp::Uint32 x = 0; x<_world->GetSizeX(); ++x)
		for(imp::Uint32 y = 0; y<_world->GetSizeY(); ++y)
		{
			int imgx = x*imgw/_world->GetSizeX();
			int imgy = y*imgh/_world->GetSizeY();

            imp::Pixel pixel = _heightmap->getPixel(imgx, imgy);
			int localElevation = (pixel.red + pixel.green + pixel.blue)/3;

			localElevation = localElevation*(unsigned int)height/256;

			int z = 0;
			for(; z<localElevation-3; ++z)
				_world->SetValue(x,y,z, 4);

			for(;z<localElevation; ++z)
				_world->SetValue(x,y,z,1);

			for(; z<(int)height; ++z)
				_world->SetValue(x,y,z,0);
		}
}

//--------------------------------------------------------------
void IGWordGenerator::InitRand()
{
    srand(time(NULL));
}

//--------------------------------------------------------------
imp::Uint32 IGWordGenerator::Rand(imp::Uint32 _min, imp::Uint32 _max)
{
    return (rand()%(_max - _min) + _min);
}
