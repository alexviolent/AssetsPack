AssetsPack
==========

文件资源打包的源代码，原理很简单，就是维护一份文件列表在pack文件的末尾，文件头记录文件列表所在的位置，中间内容都是打包的文件流。


using : AssetsPack.exe --dir "f:\assets" --root "f:\assets" --target "assets.pak"

--dir 表示要打包的文件夹

--root 表示要打包的文件夹根目录，到时候读取文件的时候用的就是相对路径，比如这里指定了root为f:\assets，有文件比如是f:\assets\bg_login.png，
代码中读取打包的资源就是用相对路径代码中读取打包的资源就是用相对路径pAssetsPack->OpenFile("bg_login.png");

--target 表示打包出的目标文件名，会生成在AssetsPack.exe同目录