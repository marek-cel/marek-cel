#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

void write();
void read();

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << std::endl;

    write();
    read();

    return 0;
}

void write()
{
    pt::ptree pt_ini;
    pt_ini.put("config.setting1", "value1");
    pt_ini.put("config.setting2", true);
    pt_ini.put("config.setting3", 3.14);
    //pt_ini.put("other.section1.option", "value3");
    pt::write_ini("config.ini", pt_ini);

    pt::ptree pt_xml;
    pt_xml.put("config.setting1", "value1");
    pt_xml.put("config.setting2", true);
    pt_xml.put("config.setting4", 3.14);
    pt_xml.put("other.section1.option", "value3");
    pt::write_xml("config.xml", pt_xml, std::locale(), pt::xml_writer_make_settings< std::string >(' ', 2));

    pt::ptree pt_json;
    pt_json.put("config.setting1", "value1");
    pt_json.put("config.setting2", true);
    pt_json.put("config.setting4", 3.14);
    pt_json.put("other.section1.option", "value3");
    pt::write_json("config.json", pt_json);
}

void read()
{
    pt::ptree pt_ini;
    pt::read_ini("../config2.ini", pt_ini);
    std::cout << "config.setting1 = " << pt_ini.get<std::string>("config.setting1") << std::endl;
    std::cout << "config.setting2 = " << pt_ini.get<bool>("config.setting2") << std::endl;
    std::cout << "config.setting3 = " << pt_ini.get<double>("config.setting3") << std::endl;
    std::cout << std::endl;

    pt::ptree pt_xml;
    pt::read_xml("../config2.xml", pt_xml);
    std::cout << "config.setting1 = " << pt_xml.get<std::string>("config.setting1") << std::endl;
    std::cout << "config.setting2 = " << pt_xml.get<bool>("config.setting2") << std::endl;
    std::cout << "config.setting4 = " << pt_xml.get<double>("config.setting4") << std::endl;
    std::cout << "other.section1.option = " << pt_xml.get<std::string>("other.section1.option") << std::endl;
    pt::ptree pt_xml_other_1 = pt_xml.get_child("other");
    std::cout << "section1.option = " << pt_xml_other_1.get<std::string>("section1.option") << std::endl;
    std::cout << std::endl;

    pt::ptree pt_json;
    pt::read_json("../config2.json", pt_json);
    std::cout << "config.setting1 = " << pt_json.get<std::string>("config.setting1") << std::endl;
    std::cout << "config.setting2 = " << pt_json.get<bool>("config.setting2") << std::endl;
    std::cout << "config.setting4 = " << pt_json.get<double>("config.setting4") << std::endl;
    std::cout << "other.section1.option = " << pt_json.get<std::string>("other.section1.option") << std::endl;
    std::cout << std::endl;
}