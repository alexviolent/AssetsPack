// AssetsPack.cpp : 定义控制台应用程序的入口点。
//
#include "AssetsOperator.h"
#include "AssetsPack.h"
#include "IFile.h"

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



int main(int argc, char* argv[])
{
    TestAddFile();

    TestReadFile();

    getchar();
    return 0;
}

