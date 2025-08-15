#include "utils.h"

#include <cassert>

void setupCameraManipulators(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments)
{
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManip = new osgGA::KeySwitchMatrixManipulator();

    keyswitchManip->addMatrixManipulator( '1', "Trackball"   , new osgGA::TrackballManipulator()   );
    keyswitchManip->addMatrixManipulator( '2', "Flight"      , new osgGA::FlightManipulator()      );
    keyswitchManip->addMatrixManipulator( '3', "Drive"       , new osgGA::DriveManipulator()       );
    keyswitchManip->addMatrixManipulator( '4', "Terrain"     , new osgGA::TerrainManipulator()     );
    keyswitchManip->addMatrixManipulator( '5', "Orbit"       , new osgGA::OrbitManipulator()       );
    keyswitchManip->addMatrixManipulator( '6', "FirstPerson" , new osgGA::FirstPersonManipulator() );
    keyswitchManip->addMatrixManipulator( '7', "Spherical"   , new osgGA::SphericalManipulator()   );

    std::string pathfile;
    double animationSpeed = 1.0;
    while(arguments->read("--speed",animationSpeed) ) {}
    char keyForAnimationPath = '8';
    while (arguments->read("-p",pathfile))
    {
        osgGA::AnimationPathManipulator* apm = new osgGA::AnimationPathManipulator(pathfile);
        if (apm || !apm->valid())
        {
            apm->setTimeScale(animationSpeed);

            unsigned int num = keyswitchManip->getNumMatrixManipulators();
            keyswitchManip->addMatrixManipulator(keyForAnimationPath, "Path", apm);
            keyswitchManip->selectMatrixManipulator(num);
            ++keyForAnimationPath;
        }
    }

    viewer->setCameraManipulator(keyswitchManip.get());
}

void setupEventHandlers(osgViewer::Viewer* viewer, osg::ArgumentParser* arguments)
{
    // add the state manipulator
    viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

    // add the thread model handler
    viewer->addEventHandler(new osgViewer::ThreadingHandler);

    // add the window size toggle handler
    viewer->addEventHandler(new osgViewer::WindowSizeHandler);

    // add the stats handler
    viewer->addEventHandler(new osgViewer::StatsHandler);

    // add the help handler
    viewer->addEventHandler(new osgViewer::HelpHandler(arguments->getApplicationUsage()));

    // add the record camera path handler
    viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);

    // add the LOD Scale handler
    viewer->addEventHandler(new osgViewer::LODScaleHandler);

    // add the screen capture handler
    viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
}

osg::Texture2D* readTextureFromFile(const char* path)
{
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(path);
    if ( image.valid() )
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
        texture->setImage(image.get());

        texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::MIRROR);
        texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::MIRROR);

        texture->setNumMipmapLevels(4);
        texture->setMaxAnisotropy(8.0);

        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST);
        texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

        return texture.release();
    }
    else
    {
        std::cerr << "Cannot open file: " << path << std::endl;
    }

    return nullptr;
}

void createDome(osg::Geometry* geom, double radius,
                bool texCoords, Projection projection,
                int lat_segments, int lon_segments)
{
    assert(lat_segments > 0);
    assert(lon_segments > 0);
    assert(radius > 0.0);

    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();

    double lat_step = osg::DegreesToRadians(180.0) / static_cast<double>(lat_segments);
    double lon_step = osg::DegreesToRadians(360.0) / static_cast<double>(lon_segments);

    double lat_prev = osg::DegreesToRadians(90.0);
    double lat_next = osg::DegreesToRadians(90.0) - lat_step;
    double lon_prev = 0.0;

    double x_prev = 0.0;
    double y_prev = 0.0;
    double z_prev = radius;

    double x_next = 0.0;
    double y_next = 0.0;
    double z_next = radius;

    double r_prev = 0.0;
    double r_next = 0.0;

    for ( int i_lat = 0; i_lat < lat_segments; ++i_lat )
    {
        if ( lat_next < osg::DegreesToRadians(-90.0) )
        {
            lat_next = osg::DegreesToRadians(-90.0);
        }

        z_prev = radius * sin(lat_prev);
        r_prev = radius * cos(lat_prev);

        for ( int i_lon = 0; i_lon < lon_segments + 1; ++i_lon )
        {
            lon_prev = i_lon * lon_step;

            x_prev = r_prev * cos(lon_prev - M_PI);
            y_prev = r_prev * sin(lon_prev - M_PI);

            z_next = radius * sin(lat_next);
            r_next = radius * cos(lat_next);

            x_next = r_next * cos(lon_prev - M_PI);
            y_next = r_next * sin(lon_prev - M_PI);

            osg::Vec3d p_prev(x_prev, y_prev, z_prev);
            osg::Vec3d p_next(x_next, y_next, z_next);

            v->push_back(p_prev);
            v->push_back(p_next);

            if ( texCoords )
            {
                if ( projection == Projection::Azimuthal )
                {
                    double n_arc_prev = (M_PI_2 - fabs(lat_prev)) / M_PI_2;
                    double n_arc_next = (M_PI_2 - fabs(lat_next)) / M_PI_2;

                    double tx_prev = 0.5 + 0.5 * n_arc_prev * sin(lon_prev);
                    double ty_prev = 0.5 + 0.5 * n_arc_prev * cos(lon_prev);
                    double tx_next = 0.5 + 0.5 * n_arc_next * sin(lon_prev);
                    double ty_next = 0.5 + 0.5 * n_arc_next * cos(lon_prev);

                    t->push_back(osg::Vec2(tx_prev, ty_prev));
                    t->push_back(osg::Vec2(tx_next, ty_next));
                }
                else if ( projection == Projection::Cylindrical )
                {
                    double tx_prev = static_cast<double>(i_lon  )/lon_segments;
                    double ty_prev = static_cast<double>(i_lat  )/lat_segments;
                    double tx_next = static_cast<double>(i_lon  )/lon_segments;
                    double ty_next = static_cast<double>(i_lat+1)/lat_segments;

                    t->push_back(osg::Vec2(tx_prev, ty_prev));
                    t->push_back(osg::Vec2(tx_next, ty_next));
                }
            }

            p_prev.normalize();
            p_next.normalize();

            n->push_back(-p_prev);
            n->push_back(-p_next);
        }

        lat_prev -= lat_step;
        lat_next -= lat_step;
    }

    c->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));

    geom->setVertexArray(v.get());
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, v->size()));

    geom->setNormalArray(n.get());
    geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

    geom->setColorArray(c.get());
    geom->setColorBinding(osg::Geometry::BIND_OVERALL);

    if ( texCoords ) geom->setTexCoordArray(0, t.get());
}

