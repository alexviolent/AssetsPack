AssetsPack
==========

文件资源打包的源代码，原理很简单，就是维护一份文件列表在pack文件的末尾，文件头记录文件列表所在的位置，中间内容都是打包的文件流。

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
