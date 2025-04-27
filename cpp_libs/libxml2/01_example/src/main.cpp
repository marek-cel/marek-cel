#include <iostream>

#include <libxml/tree.h>

int main(int argc, char* argv[])
{
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    if (doc == nullptr) {
        std::cerr << "Failed to create new XML document" << std::endl;
        return 1;
    }
    xmlNodePtr root = xmlNewNode(nullptr, BAD_CAST "root");
    std::cout << root->name << std::endl;
    if (root == nullptr) {
        std::cerr << "Failed to create new XML node" << std::endl;
        xmlFreeDoc(doc);
        return 1;
    }
    xmlDocSetRootElement(doc, root);
    xmlNodePtr child = xmlNewChild(root, nullptr, BAD_CAST "child", nullptr);
    std::cout << child->name << std::endl;
    if (child == nullptr) {
        std::cerr << "Failed to create new XML child node" << std::endl;
        xmlFreeDoc(doc);
        return 1;
    }
    xmlNodePtr subchild = xmlNewChild(child, nullptr, BAD_CAST "subchild", BAD_CAST "Hello, XML!");
    if (subchild == nullptr) {
        std::cerr << "Failed to create new XML subchild node" << std::endl;
        xmlFreeDoc(doc);
        return 1;
    }
    //xmlSaveFormatFileEnc("example.xml", doc, "UTF-8", 1);
    xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);
    xmlFreeDoc(doc);

    return 0;
}
