#include <iostream>

#include <vsg/all.h>
#include <vsgXchange/all.h>


int main(int argc, char** argv)
{
    std::cout << "Hello VulkanSceneGraph!" << std::endl;

    auto object = vsg::Object::create();
    object->setValue("name", "Adrian Mole");
    object->setValue("age", 13.75);

    if (auto auxiliary = object->getAuxiliary())
    {
        for(auto& [key, object] : auxiliary->userObjects)
        {
            if (auto s = dynamic_cast<vsg::stringValue*>(object.get())) std::cout<<"metadata key = "<<key<<", stringValue = "<<s->value()<<std::endl;
            else if (auto d = dynamic_cast<vsg::doubleValue*>(object.get())) std::cout<<"metadata key = "<<key<<", doubleValue = "<<d->value()<<std::endl;
            else std::cout<<"metadata key = "<<key<<", object = "<<object<<std::endl;
        }
    }
    else
    {
        std::cout<<"No vsg::Auxiliary assigned to Object."<<std::endl;
    }

    return 0;
}