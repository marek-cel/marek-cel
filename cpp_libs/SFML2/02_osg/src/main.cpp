#include <iostream>

#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <SFML/Window.hpp>

#include <cgi/SceneRoot.h>

template<typename G,typename W>
bool convertEvent(sf::Event& event, G gw, W window)
{
	auto eventQueue = gw->getEventQueue();

	switch (event.type)
	{
		case sf::Event::MouseMoved:
			eventQueue->mouseMotion(event.mouseMove.x, event.mouseMove.y);
			return true;

		case sf::Event::MouseButtonPressed:
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				event.mouseButton.button = static_cast<decltype(event.mouseButton.button)>(1);
			}
			else if( event.mouseButton.button == sf::Mouse::Right )
			{
				event.mouseButton.button = static_cast<decltype(event.mouseButton.button)>(3);
			}
			eventQueue->mouseButtonPress(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
			return true;

		case sf::Event::MouseButtonReleased:
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				event.mouseButton.button = static_cast<decltype(event.mouseButton.button)>(1);
			}
			else if( event.mouseButton.button == sf::Mouse::Right )
			{
				event.mouseButton.button = static_cast<decltype(event.mouseButton.button)>(3);
			}
			eventQueue->mouseButtonRelease(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
			return true;

		case sf::Event::KeyReleased:
			eventQueue->keyRelease( (osgGA::GUIEventAdapter::KeySymbol) event.key.code);
			return true;

		case sf::Event::KeyPressed:
			eventQueue->keyPress( (osgGA::GUIEventAdapter::KeySymbol) event.key.code);
			if ( event.key.code == sf::Keyboard::Escape )
			{
				window->close();
			}
			return true;

		case sf::Event::Resized:
			eventQueue->windowResize(0, 0, event.size.width, event.size.height );
			gw->resized(0, 0, event.size.width, event.size.height );
			return true;

		case sf::Event::Closed:
			window->close();
			return true;

		default:
			break;
	}

	return false;
}

int main()
{
	const int width = 800;
	const int height = 600;

    std::cout << "Hello, OSG!" << std::endl;

    sf::Window window(sf::VideoMode(width, height), "Hello, OSG!", sf::Style::Default, sf::ContextSettings(24));
    window.setFramerateLimit(60); // call it once, after creating the window

    SceneRoot sceneRoot;

    osgViewer::Viewer viewer;
    osgViewer::GraphicsWindowEmbedded* gw = viewer.setUpViewerAsEmbeddedInWindow(0,0,width,height);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	viewer.addEventHandler(new osgViewer::StatsHandler);
    viewer.realize();

    viewer.setSceneData(sceneRoot.getRootNode());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            convertEvent(event, gw, &window);
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Closing window..." << std::endl;
                window.close();
            }
        }

        viewer.frame();
        window.display();
    }

    return 0;
}