#include <float.h>
#include <math.h>

#include "mcel_adi.h"

////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

mcel_ADI::mcel_ADI( QWidget *parent ) :
    QGLWidget   ( parent ),
    
    dPixPerDeg  ( 8.0 ),
    
    dPitch_Deg  ( 0.0 ),
    dRoll_Deg   ( 0.0 )
{
    double pi = 4.0 * atan( 1.0 );
    rad2deg = 180.0 / pi;
    deg2rad = 180.0 * pi;
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::set( double dRoll_Rad, double dPitch_Rad )
{
#   ifdef WIN32
    if ( _isnan( dRoll_Rad ) || _isnan( dPitch_Rad ) ) return;
#   else
    if (  isnan( dRoll_Rad ) ||  isnan( dPitch_Rad ) ) return;
#   endif

    dRoll_Deg  = rad2deg * dRoll_Rad;
    
         if ( dPitch_Rad >  90.0 * deg2rad ) { dPitch_Deg =  90.0; }
    else if ( dPitch_Rad < -90.0 * deg2rad ) { dPitch_Deg = -90.0; }
    else
    {
        dPitch_Deg = rad2deg * dPitch_Rad;
    }

    updateGL();
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::initializeGL( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    glEnable( GL_DEPTH_TEST );

    setLighting();
    setTextures();
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::resizeGL( int iW, int iH )
{
#   ifndef Q_OS_SYMBIAN
    // OpenGL window (interior of widget)
    glViewport( 0, 0, (GLint)iW, (GLint)iH );

    // point of projection setting
    glMatrixMode( GL_PROJECTION );  // projection matrix switch
    glLoadIdentity();               // identity matrix load

    float fCoef_W = 1.0;    // width coefficient
    float fCoef_H = 1.0;    // height coefficient

    if ( iH > iW ) fCoef_H = ( (float)iH ) / ( (float)iW );
    if ( iH < iW ) fCoef_W = ( (float)iW ) / ( (float)iH );

    // orthographic projection
    glOrtho( -fCoef_W * 320.0, fCoef_W * 320.0, -fCoef_H * 320.0, fCoef_H * 320.0, 0.0, 200.0 );

    glMatrixMode( GL_MODELVIEW );
    
    glEnable( GL_DEPTH_TEST );
#   endif
}

////////////////////////////////////////////////////////////////////////////////


void mcel_ADI::paintGL( void )
{
    // preparing buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // cleaning buffers
    glLoadIdentity();                    // model-view matrix = identity matrix
    glTranslatef( 0.0, 0.0, -100.0 );    // moving scene by 100

    paintActors();
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::paintActors( void )
{
    glRotatef(  dRoll_Deg, 0, 0, 1 );
    
    glTranslatef( 0.0, -dPitch_Deg*dPixPerDeg, 0.0 );
    paintFace();
    glTranslatef( 0.0,  dPitch_Deg*dPixPerDeg, 0.0 );
    
    paintRoll();
    
    glRotatef( -dRoll_Deg, 0, 0, 1 );
    paintCase();
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::paintCase( void )
{
    glEnable( GL_TEXTURE_2D );
    
    glBindTexture( GL_TEXTURE_2D, texIndex[0] );
    
    glBegin( GL_QUADS );
    
    glColor3f( 1.0, 1.0, 1.0 );
    
#   ifdef WIN32
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -320.0, -360.0, 0.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -320.0,  360.0, 0.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  320.0,  360.0, 0.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  320.0, -360.0, 0.0 );
#   else
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -320.0, -360.0, 0.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -320.0,  360.0, 0.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  320.0,  360.0, 0.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  320.0, -360.0, 0.0 );
#   endif
    
    glEnd();

    glDisable( GL_TEXTURE_2D );
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::paintFace( void )
{
    glEnable( GL_TEXTURE_2D );
    
    glBindTexture( GL_TEXTURE_2D, texIndex[1] );
    
    glBegin( GL_QUADS );
    
    glColor3f( 1.0, 1.0, 1.0 );
    
#   ifdef WIN32
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -320.0, -1200.0, -3.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -320.0,  1200.0, -3.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  320.0,  1200.0, -3.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  320.0, -1200.0, -3.0 );
#   else    
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -320.0, -1200.0, -3.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -320.0,  1200.0, -3.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  320.0,  1200.0, -3.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  320.0, -1200.0, -3.0 );
#   endif
    
    glEnd();

    glDisable( GL_TEXTURE_2D );
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::paintRoll( void )
{
    glEnable( GL_TEXTURE_2D );
    
    glBindTexture( GL_TEXTURE_2D, texIndex[2] );
    
    glBegin( GL_QUADS );
    
    glColor3f( 1.0, 1.0, 1.0 );
    
#   ifdef WIN32
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -320.0, -360.0, -2.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -320.0,  360.0, -2.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  320.0,  360.0, -2.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  320.0, -360.0, -2.0 );
#   else
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -320.0, -360.0, -2.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -320.0,  360.0, -2.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  320.0,  360.0, -2.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  320.0, -360.0, -2.0 );
#   endif
    
    glEnd();

    glDisable( GL_TEXTURE_2D );
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::setLighting( void )
{
    glEnable( GL_LIGHTING );
    
    const float fLightIntensity = 1.0;
    
    // ambient light
    const float bgColor[3] = { fLightIntensity,
                               fLightIntensity,
                               fLightIntensity };

    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, bgColor );
    
    // material
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    
    // light color
    const float lightColor[4] = { fLightIntensity,
                                  fLightIntensity,
                                  fLightIntensity,
                                  1.0 };
                                  
    const float lightPosition[4] = { 0.0, 0.0, 100.0, 1.0 };
    
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition );
    glLightfv( GL_LIGHT1, GL_DIFFUSE,  lightColor    );
    
    glEnable( GL_LIGHT1 );
    
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

////////////////////////////////////////////////////////////////////////////////

void mcel_ADI::setTextures( void )
{
    glGenTextures( MCEL_ADI_TEX_NUM, texIndex );
    
    texIndex[0] = bindTexture( QPixmap(QString(":/gfx/case.png")), GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    texIndex[1] = bindTexture( QPixmap(QString(":/gfx/face.png")), GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    texIndex[2] = bindTexture( QPixmap(QString(":/gfx/roll.png")), GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
}
