//
//  Util.h
//  GreenApple
//
//  Created by Jacinth Nguyen on 2/23/15.
//
//

/*
    General methods unrelated to gameplay
 */

#ifndef GreenApple_Util_h
#define GreenApple_Util_h

int GetFileLength( std::istream& file )
{
    int pos = file.tellg();
    file.seekg(0, std::ios::end );
    int length = file.tellg();
    file.seekg(pos);
    
    return length;
}

void IgnoreLine( std::istream& file, int length )
{
    file.ignore( length, '\n' );
}

#endif
