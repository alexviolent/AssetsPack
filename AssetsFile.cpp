#include "AssetsFile.h"
#include "Pack.h"

AssetsFile::AssetsFile( AssetsPack* package,uint offset,uint nameHash,uint fileSize )
{
	_package=package;
	_offset=offset;
	_nameHash=nameHash;
	_size=fileSize;
}

AssetsFile::~AssetsFile()
{

}

int AssetsFile::read( uchar* buff )
{
	return _package->read(buff,_offset,_size);
}

