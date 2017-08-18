#include <stdio.h>
#include <vector>
#include "AssetsFile.h"
#ifndef __ASSETSPACK_H__
#define __ASSETSPACK_H__

typedef unsigned char uchar;
typedef unsigned int uint;


const uchar FILE_NORMAL = 1;
const uchar FILE_DELETE = 2;
const uchar FILE_COMPRESS = 3;

struct PackageHeader
{
	uint fileEntryOffset;
	int fileAmount;
};

struct FileEntry
{
	uint offset;
	uint nameHash;
	uint fileSize;
	uchar flag;
};

class AssetsPack
{
public:
	AssetsPack(const char* fileName);
	~AssetsPack();

	AssetsFile* openFile(uint hash);
	AssetsFile* openFile(const char* fileName);

	bool hasFile(const char* fileName);

	void delFile(uint hash);
	void delFile(const char* fileName);

	void addFile(uint hash,const uchar* buff,uint len);
	void addFile(const char* fileName,const uchar* buff,uint len);

	void flush();

	void mergeWith(AssetsPack* package);
	void extractTo(const char* dir);

	int read(uchar* buff,uint offset,uint len);

	bool isValid(){return _isValid;};
	std::vector<FileEntry>& getFileEntry(){return _vectorFileEntry;};

private:
	void readFileEntry();
	void writeFileEntry();

	/*获取已经删除文件的入口，如果文件大小大于等于size，就可以覆盖*/
	FileEntry* getDirtyEntry(uint size);
private:
	int _size;
	bool _isValid;

	PackageHeader _packageHeader;

	std::vector<FileEntry> _vectorFileEntry;

	FILE* _file;

	std::string _fileName;
};


#endif
