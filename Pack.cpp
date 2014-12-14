#include "Pack.h"
#include "AssetsFile.h"

uint BKDRHash(const char* str)
{
	uint seed=131;
	uint hash=0;
	int len=strlen(str);
	for (int i=0;i<len;i++)
	{
		hash=(hash*seed+str[i])&0xFFFFFFFF;
	}
	return hash&0x7FFFFFFF;
}

AssetsPack::AssetsPack( const char* fileName )
	:_file(NULL)
	,_isValid(false)
{
	_fileName=fileName;
	_file=fopen(fileName,"rb+");
	if (_file==NULL)
	{
		_file=fopen(fileName,"wb+");
		if (_file==NULL) return;
	}

	fseek(_file,0,SEEK_END);
	_size=ftell(_file);
	fseek(_file,0,SEEK_SET);

	_isValid=true;

	_packageHeader.fileAmount=0;
	_packageHeader.fileEntryOffset=sizeof(PackageHeader);

	if(_size>=8)
	{
		fread(&_packageHeader,1,sizeof(PackageHeader),_file);

		readFileEntry();
	}
	else
	{
		fwrite(&_packageHeader,1,sizeof(PackageHeader),_file);
	}
	
}

AssetsPack::~AssetsPack()
{
	if (_file!=NULL)
	{
		fclose(_file);
	}
}

void AssetsPack::readFileEntry()
{
	if (!_isValid) return;
	fseek(_file,_packageHeader.fileEntryOffset,SEEK_SET);
	for (int i=0;i<_packageHeader.fileAmount;i++)
	{
		FileEntry entry;
		fread(&entry,1,sizeof(FileEntry),_file);
		_vectorFileEntry.push_back(entry);
	}
}

void AssetsPack::writeFileEntry()
{
	fseek(_file,_packageHeader.fileEntryOffset,SEEK_SET);
	for (int i=0;i<_vectorFileEntry.size();i++)
	{
		FileEntry entry=_vectorFileEntry[i];
		fwrite(&entry,1,sizeof(FileEntry),_file);
	}
}

void AssetsPack::addFile( uint hash,const uchar* buff,uint len )
{
	delFile(hash);

	FileEntry entry;
	entry.fileSize=len;
	entry.nameHash=hash;

	FileEntry* dirtyEntry=getDirtyEntry(len);
	if (dirtyEntry!=NULL)
	{
		entry.offset=dirtyEntry->offset;
		dirtyEntry->fileSize=len;
		dirtyEntry->flag=FILE_NORMAL;
	}
	else
	{
		entry.flag=FILE_NORMAL;
		entry.offset=_packageHeader.fileEntryOffset;
		_vectorFileEntry.push_back(entry);
		_packageHeader.fileAmount++;
		_packageHeader.fileEntryOffset+=len;
	}

	fseek(_file,entry.offset,SEEK_SET);
	fwrite(buff,1,len,_file);
	
}

void AssetsPack::addFile( const char* fileName,const uchar* buff,uint len )
{
	uint hash=BKDRHash(fileName);

	addFile(hash,buff,len);
}

AssetsFile* AssetsPack::openFile( uint hash )
{
	for (uint i=0;i<_vectorFileEntry.size();i++)
	{
		FileEntry& entry=_vectorFileEntry[i];
		if (entry.flag!=FILE_DELETE&&entry.nameHash==hash)
		{
			AssetsFile* file=new AssetsFile(this,entry.offset,entry.nameHash,entry.fileSize);
			return file;
		}
	}
	return NULL;
}

AssetsFile* AssetsPack::openFile( const char* fileName )
{
	uint hash=BKDRHash(fileName);

	return openFile(hash);
}

void AssetsPack::flush()
{
	writeFileEntry();

	fseek(_file,0,SEEK_SET);
	fwrite(&_packageHeader,1,sizeof(PackageHeader),_file);

	fclose(_file);
	_file=fopen(_fileName.c_str(),"rb+");

}

int AssetsPack::read( uchar* buff,uint offset,uint len )
{
	fseek(_file,offset,SEEK_SET);
	uint r=fread(buff,1,len,_file);
	return r;
}

bool AssetsPack::hasFile( const char* fileName )
{
	uint hash=BKDRHash(fileName);
	for (uint i=0;i<_vectorFileEntry.size();i++)
	{
		FileEntry& entry=_vectorFileEntry[i];
		if (entry.flag!=FILE_DELETE&&entry.nameHash==hash)
		{
			return true;
		}
	}
	return false;
}

void AssetsPack::delFile( uint hash )
{
	for (uint i=0;i<_vectorFileEntry.size();i++)
	{
		FileEntry& entry=_vectorFileEntry[i];
		if (entry.flag!=FILE_DELETE&&entry.nameHash==hash)
		{
			entry.flag=FILE_DELETE;
			return;
		}
	}
}

void AssetsPack::delFile( const char* fileName )
{
	uint hash=BKDRHash(fileName);
	delFile(hash);
}

void AssetsPack::mergeWith( AssetsPack* package )
{
	std::vector<FileEntry> vectorFileEntry=package->getFileEntry();
	if (vectorFileEntry.size()<=0) return;

	uchar* buff=(uchar*)malloc(1024*1024*10);
	for (uint i=0;i<vectorFileEntry.size();i++)
	{
		FileEntry entry=vectorFileEntry[i];
		AssetsFile* file=package->openFile(entry.nameHash);
		if (file!=NULL)
		{
			uint size=file->getSize();
			file->read(buff);
			addFile(file->getNameHash(),buff,size);
		}
	}
	free(buff);
	flush();
}

void AssetsPack::extractTo( const char* dir )
{
	for (uint i=0;i<_vectorFileEntry.size();i++)
	{
		FileEntry& entry=_vectorFileEntry[i];
		if (entry.flag!=FILE_DELETE)
		{
			
		}
	}
}

FileEntry* AssetsPack::getDirtyEntry( uint size )
{
	for (uint i=0;i<_vectorFileEntry.size();i++)
	{
		FileEntry* entry=&_vectorFileEntry[i];
		if (entry->flag==FILE_DELETE)
		{
			if (entry->fileSize>=size)
			{
				return entry;
			}
		}
	}
	return NULL;
}

