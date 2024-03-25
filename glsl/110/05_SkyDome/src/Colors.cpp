#include <Colors.h>

const osg::Vec3 Colors::black = osg::Vec3( 0.00f, 0.00f, 0.00f );
const osg::Vec3 Colors::white = osg::Vec3( 1.00f, 1.00f, 1.00f );

const osg::Vec3 Colors::blue    = osg::Vec3( 0.00f, 0.00f, 1.00f );
const osg::Vec3 Colors::cyan    = osg::Vec3( 0.00f, 1.00f, 1.00f );
const osg::Vec3 Colors::green   = osg::Vec3( 0.00f, 0.50f, 0.00f );
const osg::Vec3 Colors::grey    = osg::Vec3( 0.50f, 0.50f, 0.50f );
const osg::Vec3 Colors::lime    = osg::Vec3( 0.00f, 1.00f, 0.00f );
const osg::Vec3 Colors::magenta = osg::Vec3( 1.00f, 0.00f, 1.00f );
const osg::Vec3 Colors::maroon  = osg::Vec3( 0.50f, 0.00f, 0.00f );
const osg::Vec3 Colors::navy    = osg::Vec3( 0.00f, 0.00f, 0.50f );
const osg::Vec3 Colors::olive   = osg::Vec3( 0.50f, 0.50f, 0.00f );
const osg::Vec3 Colors::orange  = osg::Vec3( 1.00f, 0.65f, 0.00f );
const osg::Vec3 Colors::purple  = osg::Vec3( 0.50f, 0.00f, 0.50f );
const osg::Vec3 Colors::red     = osg::Vec3( 1.00f, 0.00f, 0.00f );
const osg::Vec3 Colors::teal    = osg::Vec3( 0.00f, 0.50f, 0.50f );
const osg::Vec3 Colors::yellow  = osg::Vec3( 1.00f, 1.00f, 0.00f );

const osg::Vec3 Colors::amber = osg::Vec3( 1.00f, 0.75f, 0.00f );

const osg::Vec3 Colors::haze[] = {
    osg::Vec3(   5.0f/255.0f,   5.0f/255.0f,   8.0f/255.0f ), //  0) 05:20 (-10 deg)
    osg::Vec3(  45.0f/255.0f,  45.0f/255.0f,  47.0f/255.0f ), //  1) 05:30 ( -7 deg)
    osg::Vec3(  85.0f/255.0f,  86.0f/255.0f,  87.0f/255.0f ), //  2) 05:40 ( -5 deg)
    osg::Vec3( 126.0f/255.0f, 126.0f/255.0f, 126.0f/255.0f ), //  3) 05:50 ( -2 deg)
    osg::Vec3( 168.0f/255.0f, 168.0f/255.0f, 166.0f/255.0f ), //  4) 06:00 (  0 deg)
    osg::Vec3( 169.0f/255.0f, 175.0f/255.0f, 183.0f/255.0f ), //  5) 06:10 (  3 deg)
    osg::Vec3( 173.0f/255.0f, 184.0f/255.0f, 201.0f/255.0f ), //  6) 06:20 (  5 deg)
    osg::Vec3( 177.0f/255.0f, 193.0f/255.0f, 219.0f/255.0f ), //  7) 06:30 (  8 deg)
    osg::Vec3( 182.0f/255.0f, 203.0f/255.0f, 238.0f/255.0f )  //  8) 06:40 ( 10 deg)
};

const osg::Vec3 Colors::sky[] = {
    osg::Vec3(   3.0f/255.0f,   3.0f/255.0f,   7.0f/255.0f ), //  0) 05:20 (-10 deg)
    osg::Vec3(  21.0f/255.0f,  25.0f/255.0f,  35.0f/255.0f ), //  1) 05:30 ( -7 deg)
    osg::Vec3(  39.0f/255.0f,  48.0f/255.0f,  63.0f/255.0f ), //  2) 05:40 ( -5 deg)
    osg::Vec3(  57.0f/255.0f,  71.0f/255.0f,  91.0f/255.0f ), //  3) 05:40 ( -2 deg)
    osg::Vec3(  76.0f/255.0f,  94.0f/255.0f, 119.0f/255.0f ), //  4) 06:00 (  0 deg)
    osg::Vec3(  71.0f/255.0f,  98.0f/255.0f, 137.0f/255.0f ), //  5) 06:10 (  3 deg)
    osg::Vec3(  66.0f/255.0f, 102.0f/255.0f, 156.0f/255.0f ), //  6) 06:20 (  5 deg)
    osg::Vec3(  61.0f/255.0f, 107.0f/255.0f, 175.0f/255.0f ), //  7) 06:30 (  8 deg)
    osg::Vec3(  57.0f/255.0f, 112.0f/255.0f, 194.0f/255.0f )  //  8) 06:40 ( 10 deg)
};

const osg::Vec3 Colors::fog[] = {
    osg::Vec3(   6.0f/255.0f,   4.0f/255.0f,   6.0f/255.0f ), //  0) 05:20 (-10 deg)
    osg::Vec3(  46.0f/255.0f,  43.0f/255.0f,  45.0f/255.0f ), //  1) 05:30 ( -7 deg)
    osg::Vec3(  86.0f/255.0f,  82.0f/255.0f,  84.0f/255.0f ), //  2) 05:40 ( -5 deg)
    osg::Vec3( 126.0f/255.0f, 121.0f/255.0f, 123.0f/255.0f ), //  3) 05:40 ( -2 deg)
    osg::Vec3( 166.0f/255.0f, 160.0f/255.0f, 162.0f/255.0f ), //  4) 06:00 (  0 deg)
    osg::Vec3( 184.0f/255.0f, 179.0f/255.0f, 181.0f/255.0f ), //  5) 06:10 (  3 deg)
    osg::Vec3( 201.0f/255.0f, 198.0f/255.0f, 200.0f/255.0f ), //  6) 06:20 (  5 deg)
    osg::Vec3( 219.0f/255.0f, 217.0f/255.0f, 219.0f/255.0f ), //  7) 06:30 (  8 deg)
    osg::Vec3( 236.0f/255.0f, 236.0f/255.0f, 238.0f/255.0f )  //  8) 06:40 ( 10 deg)
};

const osg::Vec3 Colors::sun[] = {
    osg::Vec3( 249.0f/255.0f, 216.0f/255.0f, 163.0f/255.0f ), //  0
    osg::Vec3( 249.0f/255.0f, 218.0f/255.0f, 169.0f/255.0f ), //  1
    osg::Vec3( 250.0f/255.0f, 221.0f/255.0f, 177.0f/255.0f ), //  2
    osg::Vec3( 250.0f/255.0f, 224.0f/255.0f, 184.0f/255.0f ), //  3
    osg::Vec3( 251.0f/255.0f, 226.0f/255.0f, 191.0f/255.0f ), //  4
    osg::Vec3( 251.0f/255.0f, 229.0f/255.0f, 198.0f/255.0f ), //  5
    osg::Vec3( 252.0f/255.0f, 232.0f/255.0f, 205.0f/255.0f ), //  6
    osg::Vec3( 253.0f/255.0f, 234.0f/255.0f, 212.0f/255.0f ), //  7
    osg::Vec3( 253.0f/255.0f, 237.0f/255.0f, 219.0f/255.0f ), //  8
    osg::Vec3( 254.0f/255.0f, 240.0f/255.0f, 227.0f/255.0f ), //  9
    osg::Vec3( 255.0f/255.0f, 253.0f/255.0f, 250.0f/255.0f )  // 10
};

const osg::Vec3 Colors::moon = osg::Vec3( 0.05f, 0.05f, 0.05f );

