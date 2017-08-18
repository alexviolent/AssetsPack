/*!
 * @file IFile.h
 * @date 2017/08/18 13:56
 *
 * @author 阿力(qq:395942144)
 *
 * @brief 文件接口
 *
*/
#ifndef IFILE_H
#define IFILE_H
#include "Macros.h"
class IFile
{
public:
	virtual uint GetFileSize() = 0; // 获取文件大小
	virtual uint Read(uchar* pBuffer) = 0; // 读取文件字节
	virtual uchar* GetBuffer() = 0; // 获取文件字节
};
#endif // !IFILE_H
