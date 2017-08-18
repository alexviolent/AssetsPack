#ifndef __ASSETSFILE_H__
#define __ASSETSFILE_H__

class AssetsPack;

class AssetsFile
{
public:
	AssetsFile(AssetsPack* package,unsigned int offset,unsigned int nameHash,unsigned int fileSize);
	~AssetsFile();

	int read(unsigned char* buff);

	//int compress();
	//int unCompress();

	unsigned int getSize(){return _size;};
	unsigned int getNameHash(){return _nameHash;};

private:
	bool _isCompressed;
	unsigned int _size;
	unsigned int _offset;
	unsigned int _nameHash;

	AssetsPack* _package;
};


#endif
