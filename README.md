AssetsPack
==========

文件资源打包的源代码，原理很简单，就是维护一份文件列表在pack文件的末尾，文件头记录文件列表所在的位置，中间内容都是打包的文件流。


using : AssetsPack.exe --dir "f:\assets" --root "f:\assets" --target "assets.pak"