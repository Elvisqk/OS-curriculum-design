# 记录1
OpenFile:: WriteBack()的功能是将该文件的文件头(FCB、i-node)写入硬盘
相应的扇区中；
# 记录2
code/lab5/main.cc 模块中新添加了三个Nachos 文件系统命令：  
(a)nachos [-d f] -ap Unix_filename Nachos_filename  
该命令的功能是将一个 UNIX 文件(unix_filename)附加到一个 Nachos 文件
(nachos_filename)的 后面，目的是用来测试当我们在一个Nachos的文件尾部追加数据后，文件大小是否会增加；  
(b)nachos [-d f] -hap Unix_filename Nachos_filename  
该命令的功能是从一个Nachos文件(nachos_filename)的 中间(文件大小的1/2)位置开始，将一个UNIX 文件(unix_filename)写入到该 Nachos 文件中。如果这个UNIX文件大于Nachos文件的一半，则该目录执行后，新的Nachos文件的大小将增加。  
上述两个命令调用了fstest.cc中的Append(…)函数。  
(c)nachos [-d f] -nap Nachos_filename1 Nachos_filename1  
该命令的功能是将一个Nachos 文件(unix_filename1)附加到一个 Nachos 文件(nachos_filename2)的后面，目的是用来测试当我们在一个Nachos的文件尾部写入数据时，文件大写是否会增加； 
该命令调用了fstest.cc 中的NAppend(…)函数。 
注意：只有你在OpenFile类中自己编写代码实现了函数WriteBack()的功能，并在这两个函数 Append(…)与 NAppend(…)中去掉语句//openFile->WriteBack();或// openFileTo->WriteBack();注释，上述三个命令才能正常执行。
# 记录3
(1)需要修改哪些模块，需要使用哪些不需要修改的模块；  
需要修改的模块：  
openfile.h中的OpenFile类  
filehdr.h中的FileHeader类  
filesystem.h中的FileSystem类  
fstest.cc中的Append()函数及NAppend()函数  
需要使用但不需要修改的模块：  
bitmip.h中的BitMap 类  
(2)在那些需要修改的模块中，哪些函数需要修改，如何修改；  
①修改openfile.cc中的OpenFile::WriteAt()允许从文件尾部开始写数据，并可为要写入的数据分配新的扇区；  
②修改FileSystem 类，添加空闲块位示图文件的硬盘读写操作；  
③修改OpenFile::OpenFile()及OpenFile::WriteBack()，实现文件头的硬盘读写；  
④修改FileHeader::Allocate()，为添加的数据分配硬盘块（扇区）；  
⑤修改fstest.cc的Append()函数，使下次的写指针指向新写入数据的尾部，并在扩展操作结束后调用OpenFile::WriteBack()将修改后的文件头写入硬盘；  
(3)在那些需要修改的模块中，是否需要添加函数与变量；  
中需要添加的函数  
OpenFile中添加私有变量int hdrSector;  
(4)是否需要在修改的模块中移动变量，或者从一个模块移动到另一个模块；  
# 记录4
这个实验，看着唬人，其实不怎么难，说是要修改这一堆文件，但是实际上，指南都改好了，甚至贴心得将需要改的代码用框框给框了起来，我们只需要负责copy就行了，没有需要自己动脑来修改的文件。难的在于看懂为什么这么改。如果仔细看过实验四的指南的话，这部分应该会好看很多。