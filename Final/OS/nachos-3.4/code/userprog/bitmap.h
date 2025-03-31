// bitmap.h 
//	Data structures defining a bitmap -- an array of bits each of which
//	can be either on or off.
//
//	Represented as an array of unsigned integers, on which we do
//	modulo arithmetic to find the bit we are interested in.
//
//	The bitmap can be parameterized with with the number of bits being 
//	managed.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef BITMAP_H
#define BITMAP_H

#include "copyright.h"
#include "utility.h"
#include "openfile.h"

// Definitions helpful for representing a bitmap as an array of integers
#define BitsInByte 	8
#define BitsInWord 	32

// The following class defines a "bitmap" -- an array of bits,
// each of which can be independently set, cleared, and tested.
//
// Most useful for managing the allocation of the elements of an array --
// for instance, disk sectors, or main memory pages.
// Each bit represents whether the corresponding sector or page is
// in use or free.

class BitMap {
  public:
    BitMap(int nitems);		// Initialize a bitmap, with "nitems" bits
    // 初始化一个拥有“nitems”比特的BitMap
				// initially, all bits are cleared.
    ~BitMap();			// De-allocate bitmap
    
    void Mark(int which);   	// Set the "nth" bit
    // 标记which位置的bit位
    void Clear(int which);  	// Clear the "nth" bit
    // 清除which位置的bit位
    bool Test(int which);   	// Is the "nth" bit set?
    // 测试which位置的bit位是0还是1
    int Find();// Return the # of a clear bit, and as a side effect, set the bit. If no bits are clear, return -1.
    // 找一个为0的bit位，置1并返回位置which，若没有，则返回-1
    int NumClear();		// Return the number of clear bits
    // 返回全为0的比特位
    void Print();		// Print contents of bitmap
    // 打印全部位示图
    // These aren't needed until FILESYS, when we will need to read and 
    // write the bitmap to a file
    void FetchFrom(OpenFile *file); 	// fetch contents from disk
    // 从file文件中得到位示图
    void WriteBack(OpenFile *file); 	// write contents to disk
    // 将位示图写入file文件
  private:
    int numBits;			// number of bits in the bitmap
    // 比特位的数量
    int numWords;   // 字的数量
    // number of words of bitmap storage
		// (rounded up if numBits is not a
		//  multiple of the number of bits in
		//  a word)
    unsigned int *map;			// bit storage
    // 位示图
};

#endif // BITMAP_H
