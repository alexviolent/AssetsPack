/*!
 * @file AssetsFile.h
 * @date 2017/08/18 14:50
 *
 * @author 阿力(qq:395942144)
 *
 * @brief 资源包虚拟的文件对象
 *
*/
#ifndef ASSETS_FILE_H
#define ASSETS_FILE_H
#include "IFile.h"
#include "Macros.h"

class IAssetsOperator;
class CAssetsFile : public IFile
{
public:
    CAssetsFile(IAssetsOperator* pAssetsOperator, uint nFileOffset, uint nFileSize);
    ~CAssetsFile();

    virtual uint GetFileSize() override;
    virtual uint Read(uchar* pBuffer) override;
    virtual uchar* GetBuffer() override;

private:
    IAssetsOperator* m_pAssetsOperator;
    uint m_nFileOffset;
    uint m_nFileSize;
};
#endif // !ASSETS_FILE_H



