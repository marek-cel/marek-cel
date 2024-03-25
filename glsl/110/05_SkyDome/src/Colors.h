#ifndef COLORS_H
#define COLORS_H

#include <osg/Vec3>

struct Colors
{
    static const osg::Vec3 black;       ///< black
    static const osg::Vec3 white;       ///< white

    static const osg::Vec3 blue;        ///< cyan    (according to W3C)
    static const osg::Vec3 cyan;        ///< cyan    (according to W3C)
    static const osg::Vec3 green;       ///< green   (according to W3C)
    static const osg::Vec3 grey;        ///< grey    (according to W3C)
    static const osg::Vec3 lime;        ///< lime    (according to W3C)
    static const osg::Vec3 magenta;     ///< magenta (according to W3C)
    static const osg::Vec3 maroon;      ///< maroon  (according to W3C)
    static const osg::Vec3 navy;        ///< navy    (according to W3C)
    static const osg::Vec3 olive;       ///< olive   (according to W3C)
    static const osg::Vec3 orange;      ///< orange  (according to W3C)
    static const osg::Vec3 purple;      ///< purple  (according to W3C)
    static const osg::Vec3 red;         ///< red     (according to W3C)
    static const osg::Vec3 teal;        ///< teal    (according to W3C)
    static const osg::Vec3 yellow;      ///< yellow  (according to W3C)

    static const osg::Vec3 amber;      ///< amber

    static const osg::Vec3 hud;        ///< HUD color

    static const osg::Vec3 sky[9];      ///< clear sky horizon color
    static const osg::Vec3 haze[9];      ///< clear sky horizon color
    static const osg::Vec3 fog[9];      ///< foggy sky horizon color

    static const osg::Vec3 sun[11];     ///< sun light color
    static const osg::Vec3 moon;        ///< moon light color
};

#endif // COLORS_H
