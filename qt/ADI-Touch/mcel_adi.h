#ifndef _MCEL_ADI_H_
#define _MCEL_ADI_H_

////////////////////////////////////////////////////////////////////////////////

#define MCEL_ADI_TEX_NUM 3

////////////////////////////////////////////////////////////////////////////////

#include <QGLWidget>

////////////////////////////////////////////////////////////////////////////////

/** @author Marek Cel (mcel@mcel.pl) */
class mcel_ADI : public QGLWidget
{
    Q_OBJECT
    
private:

    GLuint  texIndex[MCEL_ADI_TEX_NUM];
    
    double  dPixPerDeg;     ///< [pix/deg]
    
    double  dPitch_Deg;     ///< [deg] pitch angle
    double  dRoll_Deg;      ///< [deg] roll angle

    double  deg2rad;        ///<
    double  rad2deg;        ///<

public:

    /** */
    mcel_ADI( QWidget *parent = 0 );
    
    /** */
    void set( double dRoll_Rad, double dPitch_Rad );

protected:

    /**
     * This function renders the OpenGL scene and. It is called whenever the widget
     * needs to be updated. */
    void initializeGL();

    /**
     * This function sets up the OpenGL viewport, projection, etc. It is called
     * whenever the widget has been resized. */
    void resizeGL( int iW, int iH );

    /**
     * This function sets up the OpenGL rendering context, defines display lists.
     * It is called once before the first time resizeGL() or paintGL() is called. */
    void paintGL();

    /** */
    void paintActors();

    /** */
    void paintCase();
    
    /** */
    void paintFace();
    
    /** */
    void paintRoll();
    
    /** */
    void setLighting();

    /** */
    void setTextures();
};

////////////////////////////////////////////////////////////////////////////////

#endif // _MCEL_ADI_H_
