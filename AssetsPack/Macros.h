/*!
 * @file Macros.h
 * @date 2017/08/18 12:13
 *
 * @author 阿力(qq:395942144)
 *
 * @brief 宏定义
 *
*/
#ifndef MACROS_H
#define MACROS_H

typedef unsigned char uchar;
typedef unsigned int uint;

// 文件标志FileFlag
static const uchar FF_NORMAL = 1;     // 普通文件
static const uchar FF_DELETE = 2;        // 已删除的文件
static const uchar FF_COMPRESS = 3;  // 已压缩的文件
//
#define XXHASH32(_STR_) XXH32(_STR_, strlen(_STR_), 0x123ABC89)
//
#define BREAK_IF(_COND_) if (_COND_) break;
//
#define FE_FOREACH(_VAR_, _T_) FileEntry* _VAR_ = NULL; \
for (std::set<FileEntry>::iterator it = _T_.begin(); it != _T_.end() ? _VAR_ = (FileEntry*)&(*it) : _VAR_ = NULL; it++)

#endif // !MACROS_H
