// AssetsPack.cpp : 定义控制台应用程序的入口点。
//
#include "AssetsOperator.h"
#include "AssetsPack.h"
#include "IFile.h"
#include <io.h>
#include <vector>
#include <fstream>

void TestAddFile()
{
    CAssetsPack* pAssetsPack = new CAssetsPack(CAssetsOperator::GetInstance());

    if(pAssetsPack->LoadPackFile("F:\\TestPackFile.dat"))
    {
        pAssetsPack->AddFile("ui\\LoginView\\bg.png", (const uchar*)"1234\0", 5);
        pAssetsPack->SavePack();
    }

    delete pAssetsPack;
}

void TestReadFile()
{
    CAssetsPack* pAssetsPack = new CAssetsPack(CAssetsOperator::GetInstance());

    do
    {
        BREAK_IF(!pAssetsPack->LoadPackFile("F:\\TestPackFile.dat"))

        IFile* pFile = pAssetsPack->OpenFile("ui\\LoginView\\bg.png");

        BREAK_IF(!pFile)

        uchar* pBuffer = pFile->GetBuffer();

        BREAK_IF(!pBuffer)

        pFile->Read(pBuffer);
        printf((const char*)pBuffer);

        delete pBuffer;
    }
    while(0);

    pAssetsPack->Close();
    delete pAssetsPack;
}

using std::string;
using std::vector;
using std::ios;

enum
{
	kNone,
	kSrcDir,
	kSrcRoot,
	kPackedFile
};

static string src_dir = "";
static string src_root = "";
static string packed_file = "def.pak";
static vector<string> all_files;

static int cur_cmd_kind = kNone;

void parse_value(char* arg)
{
	switch (cur_cmd_kind)
	{
	case kSrcDir:
		src_dir = arg;
		break;
	case kSrcRoot:
		src_root = arg;
		break;
	case kPackedFile:
		packed_file = arg;
		break;
	default:
		break;
	}
	cur_cmd_kind = kNone;
}

void parse_key(char* arg)
{
	if (cur_cmd_kind != kNone)
	{
		parse_value(arg);
		return;
	}

	if (strcmpi(arg, "--dir") == 0)
	{
		cur_cmd_kind = kSrcDir;
	}
	else if (strcmpi(arg, "--root") == 0)
	{
		cur_cmd_kind = kSrcRoot;
	}
	else if (strcmpi(arg, "--target") == 0)
	{
		cur_cmd_kind = kPackedFile;
	}
	else
	{
		parse_value(arg);
	}

}

void list_files(const string& root)
{
	struct _finddata_t files;
	int file_handle;
	file_handle = _findfirst((root+"\\*.*").c_str(), &files);
	if (file_handle == -1)
	{
		printf("error\n");
		return;
	}
	do
	{
		if (strcmpi(files.name,".") == 0 || 
			strcmpi(files.name,"..") == 0)
		{
		}
		else
		{
			if (files.attrib == _A_SUBDIR)
			{
				list_files(root+"\\"+files.name);
			}
			else
			{
				all_files.push_back(root + "\\" + files.name);
			}
		}

	} while (0 == _findnext(file_handle, &files));
	_findclose(file_handle);
}

int pack()
{
	all_files.clear();
	list_files(src_dir);

	remove(packed_file.c_str());

	CAssetsPack* assets_pack = new CAssetsPack(CAssetsOperator::GetInstance());

	if (!assets_pack->LoadPackFile(packed_file.c_str()))
	{
		return -1;
	}

	for (size_t i = 0; i < all_files.size(); i++)
	{
		string filepath = all_files[i];
		std::ifstream fin(filepath.c_str(), ios::binary);
		if (fin.good())
		{
			fin.seekg(0, ios::end);
			int file_size = fin.tellg();
			fin.seekg(0, ios::beg);
			char* buffer = new char[file_size];
			fin.read(buffer, file_size);
			if (src_root.size()>0)
			{
				filepath = filepath.substr(src_root.size() + 1, 256);
			}
			assets_pack->AddFile(filepath.c_str(), (const uchar*)buffer, file_size);
			fin.close();
			delete buffer;
		}
	}

	assets_pack->SavePack();

	return 0;
}

int main(int argc, char* argv[])
{

	for (int i = 1; i < argc;i++)
    {
		char* arg = argv[i];
		parse_key(arg);
    }

	printf("source dir: %s\n", src_dir.c_str());
	printf("source root: %s\n", src_root.c_str());
	printf("target packed file: %s\n", packed_file.c_str());
	printf("start packing...\n");

	if (pack() == 0)
	{
		printf("success!!!\n");
	}
	else
	{
		printf("pack failure!!!\n");
	}
#if _DEBUG
    getchar();
#endif
    return 0;
}

