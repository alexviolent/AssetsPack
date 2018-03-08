#include "AssetsFile.h"
#include "IAssetsOperator.h"


CAssetsFile::CAssetsFile(IAssetsOperator* pAssetsOperator, uint nFileOffset, uint nFileSize)
    : m_pAssetsOperator(pAssetsOperator)
    , m_nFileSize(nFileSize)
    , m_nFileOffset(nFileOffset)
{

}

CAssetsFile::~CAssetsFile()
{
}

uint CAssetsFile::GetFileSize()
{
    return m_nFileSize;
}

uint CAssetsFile::Read(uchar* pBuffer)
{
    return m_pAssetsOperator->Read(pBuffer, m_nFileOffset, m_nFileSize);
}

uchar* CAssetsFile::GetBuffer()
{
    uchar* pBuffer = new(std::nothrow) uchar[m_nFileSize];

    if(pBuffer)
    {
        Read(pBuffer);
    }

    return pBuffer;
}
